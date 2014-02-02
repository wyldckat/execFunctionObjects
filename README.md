execFunctionObjects
===================

This utility was derived from OpenFOAM® 2.2.x (commit 5f924eaa18a2a1695cea21eb1f8b30ac8d463145) own `execFlowFunctionObjects` utility.

The objective was to keep this utility as basic as possible and purely reliant on the function objects themselves.

This means that there are no fields, no turbulence models and no thermodynamic models loaded by default. Anything needed should be provided by the function objects and the `libs` entry in controlDict.
Therefore, either specifically create the function objects for the features needed or rely on Third-Party function objects, such as the ones provided by swak4Foam:  http://openfoamwiki.net/index.php/Contrib/swak4Foam

As for OpenFOAM's own `execFlowFunctionObjects` utility, it it able to either run function objects on the usual U and p fields, or it will load all of the fields if the option `-noFlow` is given. For more information, see: http://openfoamwiki.net/index.php/ExecFlowFunctionObjects

If you have any questions about this `execFunctionObjects`, please use the following forum thread: http://www.cfd-online.com/Forums/openfoam-post-processing/122945-execfunctionobjects-minimalistic-variant-execflowfunctionobjects-utility.html

*NOTE:* You must use the latest OpenFOAM 2.2.x or this function object will not work as intended!! If you are using an older version of OpenFOAM, then try running:
```
execFlowFunctionObjects -noFlow
```


Disclaimer and License
======================

This offering is not approved or endorsed by OpenCFD Limited, the producer of the OpenFOAM software and owner of the OPENFOAM® and OpenCFD® trade marks.

This is bound to the same license as OpenFOAM, namely GNU Public License v3. Quoting from OpenFOAM's license statement:

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM. If not, see <http://www.gnu.org/licenses/>.



How to get+build execFunctionObjects
====================================

These instructions are for OpenFOAM 2.2.x:

For getting and building from git:
```
git clone git://github.com/wyldckat/execFunctionObjects.git
cd execFunctionObjects
git checkout master
wmake all applications
```

For getting and building from zip:
```
wget "https://github.com/wyldckat/execFunctionObjects/archive/master.zip" -O execFunctionObjects.zip
unzip execFunctionObjects.zip
cd execFunctionObjects-master
wmake all applications
```

How to use it
=============

Inside the folder `tutorials/misc/execFunctionObjects/cavity` is an example case, where:

  * `Allrun` - this script will help to run this tutorial case. Look at the contents of the file to see how it works. To run it: `./Allrun`
  * `Allclean` - this script will help clean up the tutorial case, so that you can run it again with `Allrun`.
  * `system/controlDict` - this is basically the normal `controlDict` file from the original OpenFOAM tutorial `incompressible/icoFoam/cavity`. The detail is that it has the entry `libs ();`, to keep in mind that you might need to load more libraries in order for the function objects to work.
  * `system/controlDict.functions` - this is an example of how the function objects can be configured for allowing `execFunctionObjects` to run them successfully. Notice that it first reads the necessary fields and only then it will process them accordingly.

As demonstrated in the `Allrun` script, to use the file `system/controlDict.functions` with `execFunctionObjects`, run it like this:
```
execFunctionObjects -dict system/controlDict.functions
```

For seeing all of the available options, run:
```
execFunctionObjects -help
```


Authorship
==========

This `execFunctionObjects` utility was _hacked-and-slashed_ by Bruno Santos (wyldckat@github).

Code is completely based on the original `execFlowFunctionObjects` from OpenFOAM 2.2.x, where I simply removed the excess code.

So in essence, it took longer to write this README file and to prepare the tutorial.
