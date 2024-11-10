/**
 * For now this is the only way to get a symbol in the main binary for
 * NSExtensionGetPrincipalClass for auv3 to work.
 */

#import <Foundation/Foundation.h>
#import "AudioUnitViewController.h"

@interface MyPluginAUViewController : AudioUnitViewController
@end

@implementation MyPluginAUViewController

@end
