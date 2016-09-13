//
//  OpenGLView.mm
//  -BLAM-
//
//  Created by David Riley on 10/28/09.
//  Copyright 2009 Insanely Great Software. All rights reserved.
//

#import "OpenGLView.h"
#import "CocoaGLContext.h"
#import "Texture.h"
#import "util.h"

#import "Exception.h"

#import "Image.h"

#import "Sprite.h"
#import "Event.h"
#import "Game.h"

#import <unistd.h>

#define UNICODE_FUNCTION_START 0xF700
#define UNICODE_FUNCTION_END   0xF8FF

const uint16_t gFunctionKeyTrans[] =
{
BLAM_KEY_UP_ARROW,
BLAM_KEY_DOWN_ARROW,
BLAM_KEY_LEFT_ARROW,
BLAM_KEY_RIGHT_ARROW,
BLAM_KEY_F1,
BLAM_KEY_F2,
BLAM_KEY_F3,
BLAM_KEY_F4,
BLAM_KEY_F5,
BLAM_KEY_F6,
BLAM_KEY_F7,
BLAM_KEY_F8,
BLAM_KEY_F9,
BLAM_KEY_F10,
BLAM_KEY_F11,
BLAM_KEY_F12,
BLAM_KEY_F13,
BLAM_KEY_F14,
BLAM_KEY_F15,
BLAM_KEY_UNKNOWN, // F16
BLAM_KEY_UNKNOWN, // F17
BLAM_KEY_UNKNOWN, // F18
BLAM_KEY_UNKNOWN, // F19
BLAM_KEY_UNKNOWN, // F20
BLAM_KEY_UNKNOWN, // F21
BLAM_KEY_UNKNOWN, // F22
BLAM_KEY_UNKNOWN, // F23
BLAM_KEY_UNKNOWN, // F24
BLAM_KEY_UNKNOWN, // F25
BLAM_KEY_UNKNOWN, // F26
BLAM_KEY_UNKNOWN, // F27
BLAM_KEY_UNKNOWN, // F28
BLAM_KEY_UNKNOWN, // F29
BLAM_KEY_UNKNOWN, // F30
BLAM_KEY_UNKNOWN, // F31
BLAM_KEY_UNKNOWN, // F32
BLAM_KEY_UNKNOWN, // F33
BLAM_KEY_UNKNOWN, // F34
BLAM_KEY_UNKNOWN, // F35
BLAM_KEY_INSERT,
BLAM_KEY_DELETE,
BLAM_KEY_HOME,
BLAM_KEY_UNKNOWN, // Begin
BLAM_KEY_END,
BLAM_KEY_PAGE_UP,
BLAM_KEY_PAGE_DOWN,
BLAM_KEY_PRINT_SCREEN,
BLAM_KEY_SCROLL_LOCK,
BLAM_KEY_PAUSE,
BLAM_KEY_SYSREQ,
BLAM_KEY_BREAK,
BLAM_KEY_RESET,
BLAM_KEY_STOP,
BLAM_KEY_MENU,
BLAM_KEY_USER,
BLAM_KEY_SYSTEM,
BLAM_KEY_PRINT,
BLAM_KEY_UNKNOWN, // Clear Line
BLAM_KEY_UNKNOWN, // Clear Display
BLAM_KEY_UNKNOWN, // Insert Line
BLAM_KEY_UNKNOWN, // Delete Line
BLAM_KEY_UNKNOWN, // Insert Char
BLAM_KEY_UNKNOWN, // Delete Char
BLAM_KEY_UNKNOWN, // Previous
BLAM_KEY_UNKNOWN, // Next
BLAM_KEY_UNKNOWN, // Select
BLAM_KEY_UNKNOWN, // Execute
BLAM_KEY_UNKNOWN, // Undo
BLAM_KEY_UNKNOWN, // Redo
BLAM_KEY_UNKNOWN, // Find
BLAM_KEY_HELP,
BLAM_KEY_UNKNOWN // Switch Mode
};

static const uint16_t gModKeyTrans[] =
{
BLAM_KEY_LEFT_CTRL,
BLAM_KEY_LEFT_SHIFT,
BLAM_KEY_RIGHT_SHIFT,
BLAM_KEY_LEFT_CMD,
BLAM_KEY_RIGHT_CMD,
BLAM_KEY_LEFT_OPT,
BLAM_KEY_RIGHT_OPT,
BLAM_KEY_RIGHT_CTRL
};

uint16_t map_mod(uint8_t c)
{
    uint8_t bits = c;
    for(int bit = 0; bit < 8; bit++)
    {
        if(bits & (1 << bit)) return gModKeyTrans[bit];
    }
    
    return BLAM_KEY_UNKNOWN;
}

uint16_t map_keys(NSString *chars)
{
    unichar c = [[chars lowercaseString] characterAtIndex:0];
    
    if(c >= UNICODE_FUNCTION_START && c < UNICODE_FUNCTION_END)
    {
        c = gFunctionKeyTrans[c & 0xFF];
    };
    
    return c;
}

@implementation OpenGLView

void show_hide_mouse(const NSPoint &point, const NSRect &rect, BOOL &hidden)
{
    if(NSPointInRect(point, rect))
    {
        if(!hidden)
        {
            [NSCursor hide];
            hidden = YES;
        }
    } else {
        if(hidden)
        {
            [NSCursor unhide];
            hidden = NO;
        }
    }
}

// pixel format definition
+ (NSOpenGLPixelFormat*) basicPixelFormat
{
    NSOpenGLPixelFormatAttribute attributes [] = {
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAWindow,
        NSOpenGLPFADoubleBuffer,    // double buffered
        NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16, // 16 bit depth buffer
        (NSOpenGLPixelFormatAttribute)nil
    };
    return [[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease];
}

- (void)awakeFromNib
{
    [[self window] makeFirstResponder:self];
    [[self window] setAcceptsMouseMovedEvents:YES];
    
    appThread = [[NSThread alloc] initWithTarget:self
                                        selector:@selector(run:)
                                          object:nil];
    
    NSPoint mouseLoc = [[self window] mouseLocationOutsideOfEventStream];
    
    events = new Events(Point2D(mouseLoc.x, mouseLoc.y), 1024);
        
    game = nil;
    
    [appThread start];
}



- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame pixelFormat:[OpenGLView basicPixelFormat]];
    if (self)
    {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(_surfaceNeedsUpdate:)
                                                     name:NSViewGlobalFrameDidChangeNotification
                                                   object:self];
        
    }
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}


- (void)update
{
    [super update];
    
    NSRect bounds = [self bounds];
    
    NSLog(@"Update to %fx%f",
          bounds.size.width,
          bounds.size.height);

    [[self openGLContext] update];
    
    if(game) game->updateOpenGL(bounds.size.width,
                                bounds.size.height);
    //if ([[self openGLContext] view] == self) [[self openGLContext] update];
}    


- (void)mouseMoved:(NSEvent *)evt
{

    NSPoint loc = [evt locationInWindow];
    
    Event *event = new Event(BLAM_EVENT_MOUSE_MOVED,
                             Point2D(loc.x, loc.y));
    
    events->postEvent(event);
    event->release();

    show_hide_mouse(loc,
                    [self frame],
                    mouseHidden);            
    
}

- (void)mouseDragged:(NSEvent *)evt
{
    [self mouseMoved:evt];
}

- (void)rightMouseDragged:(NSEvent *)evt
{
    [self mouseDragged:evt];
}

- (void)otherMouseDragged:(NSEvent *)evt
{
    [self mouseDragged:evt];
}

- (void)commonMouseDown:(NSEvent *)evt
{
    NSPoint loc = [evt locationInWindow];
    
    Event *event = new Event(BLAM_EVENT_MOUSE_DOWN,
                             Point2D(loc.x, loc.y));
    
    event->button = [evt buttonNumber];
    
    events->postEvent(event);
    event->release();
}

- (void)commonMouseUp:(NSEvent *)evt
{
    NSPoint loc = [evt locationInWindow];
    
    Event *event = new Event(BLAM_EVENT_MOUSE_UP,
                             Point2D(loc.x, loc.y));
    
    event->button = [evt buttonNumber];
    
    events->postEvent(event);
    event->release();
}

- (void)mouseDown:(NSEvent *)evt
{
    [self commonMouseDown:evt];
}

- (void)rightMouseDown:(NSEvent *)evt
{
    [self commonMouseDown:evt];
}

- (void)otherMouseDown:(NSEvent *)evt
{
    [self commonMouseDown:evt];
}

- (void)mouseUp:(NSEvent *)evt
{
    [self commonMouseUp:evt];
}

- (void)rightMouseUp:(NSEvent *)evt
{
    [self commonMouseUp:evt];
}

- (void)otherMouseUp:(NSEvent *)evt
{
    [self commonMouseUp:evt];
}

- (void)keyDown:(NSEvent *)evt
{
    if(![evt isARepeat])
    {
        Event *event = new Event(BLAM_EVENT_KEY_DOWN,
                                 Point2D(0, 0));
        
        event->key = map_keys([evt charactersIgnoringModifiers]);
        
        events->postEvent(event);
        event->release();
    }
}

- (void)keyUp:(NSEvent *)evt
{
    Event *event = new Event(BLAM_EVENT_KEY_UP,
                             Point2D(0, 0));
        
    event->key = map_keys([evt charactersIgnoringModifiers]);
    
    events->postEvent(event);
    event->release();
}

- (void)flagsChanged:(NSEvent *)evt
{
    static NSUInteger oldFlags = 0;
    NSUInteger flags = [evt modifierFlags];
    
    NSUInteger flagsUp = ~flags & oldFlags;
    NSUInteger flagsDown = flags & ~oldFlags;
    
    oldFlags = flags;
    
    if(flagsUp & 0xFF)
    {
        Event *event = new Event(BLAM_EVENT_KEY_UP,
                                 Point2D(0, 0));
        
        event->key = map_mod(flagsUp & 0xFF);
        
        events->postEvent(event);
        event->release();
    }
    
    if(flagsDown & 0xFF)
    {
        Event *event = new Event(BLAM_EVENT_KEY_DOWN,
                                 Point2D(0, 0));
        
        event->key = map_mod(flagsDown & 0xFF);
        
        events->postEvent(event);
        event->release();
    }
}
    
- (void)mouseEntered:(NSEvent *)evt
{
    [NSCursor hide];
}

- (void)mouseExited:(NSEvent *)evt
{
    [NSCursor unhide];
}

- (void)drawRect:(NSRect)rect
{
}

- (void)becomeActive
{
    show_hide_mouse([[self window] mouseLocationOutsideOfEventStream],
                    [self frame],
                    mouseHidden);            
}    

- (void)prepareOpenGL
{
}


- (void)run:(id)world
{
    NSOpenGLContext *gl_ctx = [self openGLContext];
    [gl_ctx setView:self];

    ctx = new CocoaGLContext(gl_ctx);
    try
    {
        game = new Game(ctx, events);
        game->initOpenGL();
        [self update];
        game->run("main.lua");
        delete game;
    }
    catch (LuaException &e)
    {
        fprintf(stderr, "Caught Lua exception: %s\n", e.why);
    }

    [[NSApplication sharedApplication] terminate:self];
}    

- (void) _surfaceNeedsUpdate:(NSNotification*)notification
{
    [self update];
    //needsUpdate = YES;
}

@end
