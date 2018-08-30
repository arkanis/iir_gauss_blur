#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define IIR_GAUSS_BLUR_IMPLEMENTATION
#include "iir_gauss_blur.h"

int main(int argc, char** argv) {
	float sigma = 10.0;
	
	char* usage = "Usage: blur [-h] [-s sigma] [-r radius16] [-R radius1] input-file output-file\n"
		"Blur an image and save it as PNG.\n";
	int opt;
	while ( (opt = getopt(argc, argv, "s:r:R:h")) != -1 ) {
		switch(opt) {
			case 's':
				sigma = strtof(optarg, NULL);
				break;
			case 'r':
				sigma = (1.0 / 1.42) * strtof(optarg, NULL);
				break;
			case 'R':
				sigma = (1.0 / 3.66) * strtof(optarg, NULL);
				break;
			case 'h':
				fprintf(stderr,
					"%s\n"
					"  -s sigma     The sigma of the gauss normal distribution (number >= 0.5).\n"
					"               Larger values result in a stronger blur.\n"
					"  -r radius16  Automatically calculate a sigma so that one pixel gets visibly\n"
					"               blurred acros that radius. A white pixel can change the\n"
					"               brightness by 16 at that radius (hence the name) which is an\n"
					"               barely visible change.\n"
					"  -R radius1   Automatically calculate a sigma so that one pixel can't change\n"
					"               other pixels outside that radius (change is lower than 1\n"
					"               brighness).\n"
					"  -h           display this help and exit.\n"
					"\n"
					"You can use either sigma, radius16 or radius1 to specify the strengh of the\n"
					"blur. If more than one is specified the last option is used.\n"
					"\n"
					"Both radius16 and radius1 are very crude approximations and work more or less\n"
					"well up to 100 (haven't tested any higher).\n"
					"\n"
					"The performance is independent of the blur strengh (sigma). This tool is an\n"
					"implementation of the paper \"Recursive implementaion of the Gaussian filter\"\n"
					"by Ian T. Young and Lucas J. van Vliet.\n"
					"\n"
					"stb_image and stb_image_write by Sean Barrett and others is used to read and\n"
					"write images.\n",
					usage
				);
				return 0;
			default:
				fprintf(stderr, "%s", usage);
				return 1;
		}
	}
	
	// Need at least two filenames after the last option
	if (argc < optind + 2) {
		fprintf(stderr, "%s", usage);
		return 1;
	}
	
	int width = 0, height = 0, components = 1;
	uint8_t* image = stbi_load(argv[optind], &width, &height, &components, 0);
	if (image == NULL) {
		fprintf(stderr, "Failed to load %s: %s.\n", argv[optind], stbi_failure_reason());
		return 2;
	}
	
	iir_gauss_blur(width, height, components, image, sigma);
	
	if ( stbi_write_png(argv[optind+1], width, height, components, image, 0) == 0 ) {
		fprintf(stderr, "Failed to save %s.\n", argv[optind+1]);
		return 3;
	}
	
	return 0;
}