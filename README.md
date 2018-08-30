# iir_gauss_blur

A command line utility to blur an image and save it as PNG. This is a simple CLI version of the iir_gauss_blur.h library.

## Usage

    ./blur [-h] [-s sigma] [-r radius16] [-R radius1] input-file output-file

`-s sigma`     The sigma of the gauss normal distribution (number >= 0.5).
               Larger values result in a stronger blur.

`-r radius16`  Automatically calculate a sigma so that one pixel gets visibly
               blurred acros that radius. A white pixel can change the
               brightness by 16 at that radius (hence the name) which is an
               barely visible change.

`-R radius1`   Automatically calculate a sigma so that one pixel can't change
               other pixels outside that radius (change is lower than 1
               brighness).

`-h`           display this help and exit.

You can use either sigma, radius16 or radius1 to specify the strengh of the
blur. If more than one is specified the last option is used.

Both radius16 and radius1 are very crude approximations and work more or less
well up to 100 (haven't tested any higher).

The performance is independent of the blur strengh (sigma). This tool is an
implementation of the paper "Recursive implementaion of the Gaussian filter"
by Ian T. Young and Lucas J. van Vliet.

stb_image and stb_image_write by Sean Barrett and others is used to read and
write images.

## Installation

- Clone the repo or download the source
- Execute `make`
- Done. Either use the `blur` executable directly or copy it somewhere in your PATH.
