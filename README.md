# Transport Gate

An audio gate controlled by transport state


## Description

This stereo audio effect outputs the input signal with an adjustable
attenuation when the hosts transport is stopped. When the transport starts the
output fades to full level with an adjustable attack time. When the transport
stops, the output fades back to the attenuated level at an adjustable release
time.

The plugin relies on the host to provide a generic UI for parameter control.


## Formats

This audio effect supports a variety of audio and plug-in frameworks:

* JACK (stand-alone command line program)
* LV2
* VST2


## Compiling

Make sure, you have installed the required build tools and libraries (see
section "Prerequisites" below) and the clone this repository (including
sub-modules) and simply run `make` in the project's root directory:

    $ git clone --recursive https://github.com/SpotlightKid/transportgate.git
    $ cd transportgate
    $ make


## Installation

After compilation has finished, copy the desired plug-in shared libraries or
bundles or the stand-alone program to the appropriate locations.

The makefile also provides an `install` target:

    make install

There is also an `install-user` target, to install the binaries in the proper
locations under the current user's home directory.

    make install-user


## Prerequisites

* The GCC C++ compiler and the usual associated software build tools
  (`make`, etc.).

  Debian / Ubuntu users should install the `build-essential` package
  to get these.

* [pkgconf]

The [LV2], [VST2] (vestige) headers are included in the [DPF] framework, which
is integrated as a Git sub-module. These need not be installed separately to
build the software in the respective plug-in formats. Some formats do have
additional dependencies, though:

* JACK client (stand-alone command line program): [JACK] development library
  and headers and pkgconf file.


## License

This software is distributed under the MIT License.

See the file [LICENSE](LICENSE) for more information.


## Author

This software was put together by *Christopher Arndt*.


## Acknowledgements

The envelope implementation is based on code from this [blog
article](https://www.earlevel.com/main/2013/06/03/envelope-generators-adsr-code/)
from [earlevel.com](https://www.earlevel.com/).

[cookiecutter-dpf-effect]: https://github.com/SpotlightKid/cookiecutter-dpf-effect
[DPF]: https://github.com/DISTRHO/DPF
[JACK]: http://jackaudio.org/
[LV2]: http://lv2plug.in/
[pkgconf]: https://github.com/pkgconf/pkgconf
[VST2]: https://en.wikipedia.org/wiki/Virtual_Studio_Technology
