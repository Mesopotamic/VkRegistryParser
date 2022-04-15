/**
 * Vulkan Registry Parser
 * We're going to download the Vulkan registry and parse it into VkClay and VkTablet headers
 */

#include <stdio.h>
#include <stdlib.h>

// The header that provides us with the access function doesn't exist on windows, so we have this weird
// workaround. The access function will let us determine if a directory exists
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

int main()
{
    // Check that the user has git executable availble in their path. system allows us to perform shell
    // commands, but in the case that they fail then it will return a non zero exit code at which point we
    // will exit out
    printf("Checking for git support : \n\n");
    int result = system("git --version");
    if (result) {
        printf("Could not find the git executable, ensure it is contained in the path\n");
        exit(-1);
    }
    printf("\nGit support confirmed!\n");

    // The next step is confirming if there is a directory containing the Vulkan-Headers git repository, if
    // not, then the repository needs to be cloned. We can check if the repository exists by using the access
    // function
    if (access("Vulkan-Headers", F_OK)) {
        printf("Vulkan-Headers repositroy does not exist, performing a git clone\n");
        system("git clone https://github.com/KhronosGroup/Vulkan-Headers.git");
    } else {
        printf("Confirmed Vulkan-Headers repository exists \n");
    }

    // Now let's open the Vulkan registry file, which is an xml file.
    FILE* xml = fopen("Vulkan-Headers/registry/vk.xml", "r");
    if (!xml) {
        printf("Failed to open vk.xml\n");
        exit(-1);
    } else {
        printf("Opened vk.xml\n");
    }
}
