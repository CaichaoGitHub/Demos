//
//  ViewController.m
//  test3DSnapshot
//
//  Created by Caichao on 15/9/14.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"
#import <OpenGLES/ES1/glext.h>

@interface ViewController ()

@property (strong) UIImageView *imageView;

@property (strong) UIImageView *comparedView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"1.png"]];
    
    self.imageView.frame = CGRectMake(50, 50, 100, 100);
    
    [self.view addSubview:self.imageView];
    
    self.comparedView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"1.png"]];
    
    self.comparedView.frame = CGRectMake(50, 200, 100, 100);
    
    [self.view addSubview:self.comparedView];
    
    [self transformImage];
    
    UIGraphicsBeginImageContext(self.view.frame.size);
    [self.view.layer.modelLayer renderInContext:UIGraphicsGetCurrentContext()];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    UIImageWriteToSavedPhotosAlbum(newImage, nil, nil, nil);
    
    BOOL opaqueBackground = YES;
    UIGraphicsBeginImageContextWithOptions(self.view.layer.bounds.size, !opaqueBackground, 0);
    [self.view drawViewHierarchyInRect:self.view.layer.bounds afterScreenUpdates:YES];
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
    
    
    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
    [dic setObject:@"a" forKey:@"1q"];
    [dic setObject:@"b" forKey:@"w2"];
    [dic setObject:@"c" forKey:@"e3"];
    [dic setObject:@"c" forKey:@"e4"];
    [dic setObject:@"c" forKey:@"e2"];
    [dic setObject:@"c" forKey:@"e1"];
    [dic setObject:@"a" forKey:@"14"];
    [dic setObject:@"b" forKey:@"a2"];
    [dic setObject:@"a" forKey:@"rq"];
    [dic setObject:@"b" forKey:@"w7"];
    [dic setObject:@"a" forKey:@"dq"];
    [dic setObject:@"b" forKey:@"ws"];
    
    NSLog(@"%@",[dic allKeys]);
    
}

#define DEGREES_TO_RADIANS(x) x * M_PI / 180

- (void)transformImage {
    float degrees = 12.0;
    float zDistance = 250;
    CATransform3D transform3D = CATransform3DIdentity;
    transform3D.m34 = 1.0 / zDistance; // the m34 cell of the matrix controls perspective, and zDistance affects the "sharpness" of the transform
    transform3D = CATransform3DRotate(transform3D, DEGREES_TO_RADIANS(degrees), 1, 0, 0); // perspective transform on y-axis
    self.imageView.layer.transform = transform3D;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

// IMPORTANT: Call this method after you draw and before -presentRenderbuffer:.
//- (UIImage*)snapshot:(UIView*)eaglview
//{
//    GLint backingWidth, backingHeight;
//    
//    // Bind the color renderbuffer used to render the OpenGL ES view
//    // If your application only creates a single color renderbuffer which is already bound at this point,
//    // this call is redundant, but it is needed if you're dealing with multiple renderbuffers.
//    // Note, replace "_colorRenderbuffer" with the actual name of the renderbuffer object defined in your class.
//    glBindRenderbufferOES(GL_RENDERBUFFER_OES, _colorRenderbuffer);
//    
//    // Get the size of the backing CAEAGLLayer
//    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
//    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
//    
//    NSInteger x = 0, y = 0, width = backingWidth, height = backingHeight;
//    NSInteger dataLength = width * height * 4;
//    GLubyte *data = (GLubyte*)malloc(dataLength * sizeof(GLubyte));
//    
//    // Read pixel data from the framebuffer
//    glPixelStorei(GL_PACK_ALIGNMENT, 4);
//    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
//    
//    // Create a CGImage with the pixel data
//    // If your OpenGL ES content is opaque, use kCGImageAlphaNoneSkipLast to ignore the alpha channel
//    // otherwise, use kCGImageAlphaPremultipliedLast
//    CGDataProviderRef ref = CGDataProviderCreateWithData(NULL, data, dataLength, NULL);
//    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
//    CGImageRef iref = CGImageCreate(width, height, 8, 32, width * 4, colorspace, kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast,
//                                    ref, NULL, true, kCGRenderingIntentDefault);
//    
//    // OpenGL ES measures data in PIXELS
//    // Create a graphics context with the target size measured in POINTS
//    NSInteger widthInPoints, heightInPoints;
//    if (NULL != UIGraphicsBeginImageContextWithOptions) {
//        // On iOS 4 and later, use UIGraphicsBeginImageContextWithOptions to take the scale into consideration
//        // Set the scale parameter to your OpenGL ES view's contentScaleFactor
//        // so that you get a high-resolution snapshot when its value is greater than 1.0
//        CGFloat scale = eaglview.contentScaleFactor;
//        widthInPoints = width / scale;
//        heightInPoints = height / scale;
//        UIGraphicsBeginImageContextWithOptions(CGSizeMake(widthInPoints, heightInPoints), NO, scale);
//    }
//    else {
//        // On iOS prior to 4, fall back to use UIGraphicsBeginImageContext
//        widthInPoints = width;
//        heightInPoints = height;
//        UIGraphicsBeginImageContext(CGSizeMake(widthInPoints, heightInPoints));
//    }
//    
//    CGContextRef cgcontext = UIGraphicsGetCurrentContext();
//    
//    // UIKit coordinate system is upside down to GL/Quartz coordinate system
//    // Flip the CGImage by rendering it to the flipped bitmap context
//    // The size of the destination area is measured in POINTS
//    CGContextSetBlendMode(cgcontext, kCGBlendModeCopy);
//    CGContextDrawImage(cgcontext, CGRectMake(0.0, 0.0, widthInPoints, heightInPoints), iref);
//    
//    // Retrieve the UIImage from the current context
//    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
//    
//    UIGraphicsEndImageContext();
//    
//    // Clean up
//    free(data);
//    CFRelease(ref);
//    CFRelease(colorspace);
//    CGImageRelease(iref);
//    
//    return image;
//}

@end
