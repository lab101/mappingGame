
#import "mainViewController.h"
#import "npDLRenderer.h"
#import "npDisplayObject.h"
#import "npBitmapSprite.h"
#import "npTweener.h"
#import "FlatRenderer.h"
#import "ImageDataLoader.h"
#import "OscSender.h"
#import "OscListener.h"
#import "AppConstants.h"
#import <CoreMotion/CoreMotion.h>
#import "cinder/Vector.h"
#import "SettingManager.h"
#import "mainController.h"
#import "npFontSprite.h"

@interface mainViewController () {
    
    CGFloat _screenWidth;
    CGFloat _screenHeight;
    
    EAGLContext *_context;

    //interfaceLayer interface;
    npDLRenderer* dlRenderer;
    
    mainController main;
    npFontSprite playerName;
    npFontSprite scoreLabel;

    
    UITextField *textField;
    UITextField *textField2;
    
    UILabel *debugLabel;
    
}

- (void)tearDownAVCapture;
- (void)setupGL;
- (void)tearDownGL;




@end

@implementation mainViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    textField = [[UITextField alloc] initWithFrame:CGRectMake( 1024/2 - (354/2) , 114, 177, 60)];

    textField.borderStyle = UITextBorderStyleRoundedRect; // or maybe UISearchBar instead?
    textField.keyboardType = UIKeyboardTypeDefault;
    textField.returnKeyType = UIReturnKeyDone;
    textField.textAlignment = UITextAlignmentLeft;
    textField.layer.borderWidth = 0;
    
    [textField setFont:[UIFont fontWithName:@"Earthbound" size:20]];

    textField.placeholder = @"VOORNAAM\n";
    textField.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
    textField.autocorrectionType = UITextAutocorrectionTypeNo;
    textField.autocapitalizationType =UITextAutocapitalizationTypeAllCharacters;
    textField.returnKeyType=UIReturnKeyDone;
    textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    [textField setDelegate:self];
     
    [self.view addSubview: textField];

    
    
    
    textField2 = [[UITextField alloc] initWithFrame:CGRectMake( 1024/2  , 114, 177, 60)];
    
    textField2.borderStyle = UITextBorderStyleRoundedRect; // or maybe UISearchBar instead?
    textField2.keyboardType = UIKeyboardTypeDefault;
    textField2.returnKeyType = UIReturnKeyDone;
    textField2.textAlignment = UITextAlignmentLeft;
    textField2.layer.borderWidth = 0;
    
    [textField2 setFont:[UIFont fontWithName:@"ITC Avant Garde Gothic" size:20]];
    
    textField2.placeholder = @"NAAM\n";
    textField2.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
    textField2.autocorrectionType = UITextAutocorrectionTypeNo;
    textField2.autocapitalizationType =UITextAutocapitalizationTypeAllCharacters;
    textField2.returnKeyType=UIReturnKeyDone;
    textField2.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    [textField2 setDelegate:self];
    
    [self.view addSubview: textField2];

    
    
    
    main.txtName = textField2;
    main.txtFirstName = textField;
    
    
    debugLabel =  [[UILabel alloc] initWithFrame:CGRectMake(20 , 20, 400, 230)];
    [debugLabel setFont:[UIFont fontWithName:@"American Typewriter" size:12]];
    debugLabel.text = @"----";
    debugLabel.backgroundColor = [UIColor clearColor];
    debugLabel.textColor = [UIColor whiteColor];

  //  [self.view addSubview: debugLabel];
    main.debugLabel = debugLabel;

        
    _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!_context) {
        NSLog(@"Failed to create ES context");
    }
    
    
    GLKView *view = (GLKView *)self.view;
    view.context = _context;
        
    self.preferredFramesPerSecond = 60;
    
    _screenWidth = [UIScreen mainScreen].bounds.size.width;
    _screenHeight = [UIScreen mainScreen].bounds.size.height;
    view.contentScaleFactor = [UIScreen mainScreen].scale;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat16;

  
    [self setupGL];
      
    dlRenderer = new npDLRenderer();    
    dlRenderer->setup();
            
    main.scoreLabel = &scoreLabel;
    main.nameLabel = &playerName;
    
    main.setup();

    
}


- (BOOL)textFieldShouldReturn:(UITextField *)aTextfield {
    
    [textField resignFirstResponder];
    
    return YES;
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    
    [self tearDownAVCapture];
    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == _context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc. that aren't in use.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Camera image orientation on screen is fixed 
    // with respect to the physical camera orientation.
    if(interfaceOrientation ==UIInterfaceOrientationLandscapeRight)return YES;
    return  NO;
}


- (void)tearDownAVCapture
{
   // [self cleanUpCaptureTextures];    
   // CFRelease(captureTextureCache);
}


- (void)setupGL
{
    [EAGLContext setCurrentContext:_context];
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:_context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    main.update();

    npTweener::update();
    
    dlRenderer->update(&main);
    dlRenderer->update(&playerName);
    dlRenderer->update(&scoreLabel);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    main.draw();
    dlRenderer->render(&main);
    
    if(playerName.isTextureReady){
        playerName.bind();
        dlRenderer->render(&playerName);
    }
    
    if(scoreLabel.isTextureReady){
        scoreLabel.bind();
        dlRenderer->render(&scoreLabel);
    }
    
    
    
    
}

#pragma mark - Touch handling methods


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    vector<ci::Vec2f> touchesVec;
    for (UITouch *touch in touches)
    {
        CGPoint location = [touch locationInView:self.view];
        ci::Vec2f touchVec;

        // check if iphone
        if([self.view frame].size.width != 1024){
            touchVec.x = location.x * 1024 / [self.view frame].size.height;
            touchVec.y = location.y * 768 / [self.view frame].size.width;
            
            //std::cout << "corrected " << touchVec.x << ":" << touchVec.y << std::endl;
        }
        
        touchesVec.push_back(touchVec);
    }
    
    main.checkToucheDown(touchesVec);
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    vector<ci::Vec2f> touchesVec;
    for (UITouch *touch in touches)
    {
        CGPoint location = [touch locationInView:self.view];
        ci::Vec2f touchVec;
        
        // check if iphone
        if([self.view frame].size.width != 1024){
            touchVec.x = location.x * 1024 / [self.view frame].size.height;
            touchVec.y = location.y * 768 / [self.view frame].size.width;
            
            //std::cout << "corrected " << touchVec.x << ":" << touchVec.y << std::endl;
        }
        
        touchesVec.push_back(touchVec);
    }
    
    main.checkToucheUp(touchesVec);
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
//    for (UITouch *touch in touches)
//    {
//        CGPoint location = [touch locationInView:self.view];        
//        //std::cout << location.x << ":" << location.y << std::endl;
//    }

}


@end
