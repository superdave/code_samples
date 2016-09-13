//
//  AppWindow.h
//  -BLAM-
//
//  Created by David Riley on 11/4/09.
//  Copyright 2009 Insanely Great Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "OpenGLView.h"

@interface AppWindow : NSWindow {
    IBOutlet OpenGLView *glView;
}

- (BOOL)isFlipped;

@end
