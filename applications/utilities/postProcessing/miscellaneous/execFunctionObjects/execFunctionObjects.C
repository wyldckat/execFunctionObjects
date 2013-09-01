/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | Unsupported Contributions for OpenFOAM
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
<2013-09-01> <Bruno Santos>: Derived execFlowFunctionObjects to a purely
  Function Objects based utility. It also relies on "libs" for loading any
  essential libraries.
-------------------------------------------------------------------------------
License
    This file is a derivative work of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    execFunctionObjects

Description
    Execute the set of functionObjects specified in the selected dictionary
    (which defaults to system/controlDict) for the selected set of times.
    Alternative dictionaries should be placed in the system/ folder.

    There are no fields loaded nor turbulence models.
    Anything needed should be provided by the function objects and the libs
    entry in controlDict.

    Therefore, either function objects for the features needed or rely on 
    Third-Party function objects, such as the ones provided by swak4Foam:
        http://openfoamwiki.net/index.php/Contrib/swak4Foam

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "timeSelector.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


int main(int argc, char *argv[])
{
    Foam::timeSelector::addOptions();
    #include "addRegionOption.H"
    #include "addDictOption.H"

    #include "setRootCase.H"
    #include "createTime.H"
    Foam::instantList timeDirs = Foam::timeSelector::select0(runTime, args);
    #include "createNamedMesh.H"

    // Construct functionObjectList

    autoPtr<functionObjectList> folPtr;
    // Externally stored dictionary for if fol constructed not from runTime
    dictionary folDict;

    if (args.optionFound("dict"))
    {
        folDict = IOdictionary
        (
            IOobject
            (
                args["dict"],
                runTime,
                IOobject::MUST_READ_IF_MODIFIED
            )
        );
        folPtr.reset(new functionObjectList(runTime, folDict));
    }
    else
    {
        folPtr.reset(new functionObjectList(runTime));
    }
    folPtr->start();


    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);

        Info<< "Time = " << runTime.timeName() << endl;

        mesh.readUpdate();

        FatalIOError.throwExceptions();

        try
        {
            folPtr().execute(true);
        }
        catch (IOerror& err)
        {
            Warning<< err << endl;
        }

        Info<< endl;
    }

    return 0;
}


// ************************************************************************* //
