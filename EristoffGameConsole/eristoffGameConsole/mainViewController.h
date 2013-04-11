
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <AVFoundation/AVFoundation.h>

void runOnMainQueueWithoutDeadlocking(void (^block)(void));
void runSynchronouslyOnVideoProcessingQueue(void (^block)(void));


@interface mainViewController : GLKViewController<UITextFieldDelegate>

@end
