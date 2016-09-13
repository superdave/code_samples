//
//  AppWindow.mm
//  -BLAM-
//
//  Created by David Riley on 11/4/09.
//  Copyright 2009 Insanely Great Software. All rights reserved.
//

#import "AppWindow.h"


@implementation AppWindow

- (void)awakeFromNib
{
}

- (BOOL)isFlipped
{
    return YES;
}

- (void)becomeMainWindow
{
    NSLog(@"I'm main!");
    
    [glView becomeActive];
}

@end
