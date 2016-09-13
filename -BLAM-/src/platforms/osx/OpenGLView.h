//
//  OpenGLView.h
//  -BLAM-
//
//  Created by David Riley on 10/28/09.
//  Copyright 2009 Insanely Great Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <ApplicationServices/ApplicationServices.h>
#import <CoreFoundation/CoreFoundation.h>
#import <Carbon/Carbon.h>

#import "GLContext.h"
#import "Game.h"
#import "Events.h"

#import "geometry.h"

@interface OpenGLView : NSOpenGLView {
    GLContext *ctx;
    
    Events *events;
    CFMachPortRef eventPort;
    
    Game *game;
    
    NSThread *appThread;
    
    BOOL mouseHidden;
    
    BOOL needsUpdate;
}

//- (void)prepareOpenGL;

- (id)initWithFrame:(NSRect)frame;

- (void)becomeActive;

- (void)commonMouseDown:(NSEvent *)evt;
- (void)commonMouseUp:(NSEvent *)evt;


- (void)run:(id)world;

@end
