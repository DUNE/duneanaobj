# `duneanaobj` - DUNE CAF format definition

## Background

End-user analysis files for the DUNE experiment are maintained in CAF ("Common Analysis File") format.
CAFs are ROOT format files that contain trees based on a custom `StandardRecord` object.

A `StandardRecord` is meant to be a sufficient summary of a neutrino event for high-level analysis.
As such they reflect properties of higher-level reconstructed objects (like tracks or showers) 
as well as summary truth information, but do not include charge, hit, or low-level timing information.
They are designed for fast iteration in analysis workflows.

CAFs are intended to have a low barrier-to-entry and be easy to use.
The only requirements for reading them are ROOT and the format description,
i.e., the `StandardRecord` object contained in this package.

If you're just looking for documentation on what's in a `StandardRecord`, 
have a look at the [Doxygen documentation pages](https://dune.github.io/duneanaobj/classcaf_1_1StandardRecord.html)
automatically generated from this repository.
(They are automatically updated whenever the `main` branch is using a GitHub Actions workflow.)

## Setting up `duneanaobj` for use 

In order to work with CAFs, you'll need to have the libraries from this package accessible to the software you want to read the CAFs with.
Depending on how you intend to read them, you may also need the development headers.

### General notes
Most users will be content with a pre-built copy of the libraries from an official source.
In this case, it is sufficient to ensure that the directory in which the libraries are located is included in the `$LD_LIBRARY_PATH` environmental variable:

```bash
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/path/to/duneanaobj/libs"
```

If you're trying to work with CAFs in compiled C++ code, you will also probably need to `#include` the `StandardRecord.h` header
and link your library or executable against the `duneanaobj` ones.
You'll then need to pass the relevant directories to your compiler and linker.
For example, for the `gcc` suite, this means `-I/path/to/StandardRecord/dir`
for the headers when compiling, and `-L/path/to/StandardRecord/libs -lStandardRecord`
for the libraries when linking.

### Using Fermilab UPS

#### Official builds
The easiest way to obtain the libraries is via the FNAL UPS system, where official builds are registered.
For example, from a Fermilab GPVM:

```bash
# first set up UPS, if you haven't already
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

# now list the available versions of duneanaobj
ups list -aK+ duneanaobj

# set up a particular version
setup duneanaobj v02_02_00 -q e20:prof
```

(If you are unfamiliar with the 'qualifiers' passed as the argument to `-q`, see [the relevant CET documentation](https://cdcvs.fnal.gov/redmine/projects/cet-is-public/wiki/AboutQualifiers).
The qualifiers you choose will need to be compatible with any other elements of your software stack.)

Setting up `duneanaobj` in this way will automatically fill the `$LD_LIBRARY_PATH` correctly.
It also sets up a `$DUNEANAOBJ_INC` you can use when compiling (with `-I` in `gcc`, for example)
and `$DUNEANAOBJ_LIB` when linking (`-L$DUNEANAOBJ_LIB -lduneanaobj_StandardRecord`) if you are building a C++ application.

#### Custom builds for development

The workflow laid out in [Building yourself](#Building yourself), below, results in a UPS product made from your copy of `duneanaobj`.
You'll need to ensure the directory that your custom product lives in conforms to the expectations of UPS.
There's a special hidden directory it must have, which I typically just copy from the central DUNE area
(you only need to do this once).
For example, I usually keep mine in `/dune/app/users/jwolcott/ups` on the GPVMs:

```bash
export MY_UPS_DIR=/dune/app/users/jwolcott/ups
cp -a /cvmfs/dune.opensciencegrid.org/products/dune/.upsfiles $MY_UPS_DIR/
```

You'll also need this directory to be known to UPS.  Make it so by adding it to `$PRODUCTS`.

```bash
export PRODUCTS=$MY_UPS_DIR:$PRODUCTS
```

Then when you list the available products, you should see any custom versions towards the top of the list.

## Reading CAFs

CAFs can be read in a number of contexts using the library in this package.

### ROOT C++ interpreter

In addition to the `$LD_LIBRARY_PATH` configuration mentioned previously,
it is also important to have the header directory listed in `$ROOT_INCLUDE_PATH`.
If you use FNAL UPS to set up `duneanaobj` as [described above](#Using Fermilab UPS),
this will be done automatically.

With those prerequisites, you can open CAFs directly:

```bash
root -l /path/to/caf.root
```

or execute a macro that reads them:

```bash
root -l -b -q /path/to/macro.C
```

## Building yourself

If you want to make modifications to the `StandardRecord` you'll probably want to build it yourself in order to test out your changes.

Check out the source of `duneanobj` (if you haven't already) from GitHub:

```bash
DUNEANAOBJ_SOURCE=/path/to/destination
git clone https://github.com/DUNE/duneanaobj.git
```

`duneanaobj` is configured to build with CMake.

### CET-style build

* Currently the build depends on the Fermilab `cetbuildtools` suite, although this requirement will hopefully be lifted in the future.
The simplest way to satisfy this dependency is again using Fermilab UPS.
Be sure to set UPS up (see above if unsure how to do that).

* You'll need to change the version that the `_CMAKE_PROJECT_VERSION_STRING` value points to
  in the `CMakeLists.txt` file in the root of the source code directory. 
  For testing, I often use `testing` as the version name, but you can pick anything that doesn't overlap with an already-existing version.
  It generally pays to make it obvious because you'll be trying to find it in a list in a minute.

* Once you've done that, choose a build area:

```bash
BUILD_AREA=/path/to/build/area
mkdir $BUILD_AREA
cd $BUILD_AREA
```

* Then use the environment preparation script supplied with this package in the `ups` directory:

```bash
. $DUNEANAOBJ_SOURCE/ups/setup_for_development -d
```

Choose `-p` for an optimized build and `-d` for a debug build. 
Be sure the check the output for errors.

* Assuming no errors, you can follow the directions from the output of `setup_for_development`

```bash
buildtool -I $MY_UPS_DIR -ivT
```

The output will be a UPS product, so you will want to keep it in a directory UPS can read.
I keep mine in `/dune/app/users/jwolcott/ups/duneanaobj` on the GPVMs, for example.

Look for `stage build SUCCESS` in the output.

* Once you have this, you should be able to load your testing version with UPS as described above in [Using Fermilab UPS](#Using Fermilab UPS).

### Standalone build

Coming soon, hopefully

## Writing CAFs

If you want to write CAFs, you should use one of the DUNE CAFMakers.
There's one for each detector suite:
* FD: [duneana/CAFMaker](https://github.com/DUNE/duneana/tree/develop/duneana/CAFMaker)
* ND: [ND_CAFMaker](https://github.com/DUNE/ND_CAFMaker)

If you're unsure how to use these tools, contact the appropriate Sim/Reco group (ND or FD), who maintain them.

## Copyright and Licensing
Copyright © 2023 FERMI NATIONAL ACCELERATOR LABORATORY for the benefit of the DUNE Collaboration.

This repository, and all software contained within, except where noted within the individual source files, is licensed under
the Apache License, Version 2.0 (the "License"); you may not use this
file except in compliance with the License. You may obtain a copy of
the License at

    http://www.apache.org/licenses/LICENSE-2.0

Copyright is granted to FERMI NATIONAL ACCELERATOR LABORATORY on behalf
of the Deep Underground Neutrino Experiment (DUNE). Unless required by
applicable law or agreed to in writing, software distributed under the
License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for
the specific language governing permissions and limitations under the
License.

# Build outside of FNAL Stack like

```
mkdir build; cd build
cmake .. -DSTANDALONE_BUILD=ON -DCMAKE_INSTALL_PREFIX=/path/to/install/dir
make install
```

This will build and install the standard record dictionary and SRProxy class. Flat class on the way.
