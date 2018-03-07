# Instructions for first time NWChemEx developers:

These are basic instructions that are not meant to be all encompassing.  
However, they should allow a beginner to our repos to build a version of NWChemEx.  
Note that the build process and repos names are currently in flux and this will 
have to be updated on a regular basis.

It is useful if you have [libint](https://github.com/evaleev/libint/releases/download/v2.4.2/libint-2.4.2.tgz) and 
[eigen](https://github.com/eigenteam/eigen-git-mirror) already installed in a 
place in your path.  So if not, get them and install them.  You will want to build 
libint with `–fPIC`.
 
It is easiest if you set the CMAKE_PREFIX_PATH in your .bashrc file.  
This is the path that cmake uses to look for packages.  For example:
```
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:$HOME/NWChemEx/install
```
(Note: `$HOME` is used throughout these instructions to denote the user's home directory.
On some machines, it might be better to use `/home/$USER`.  The point here is that `$HOME` 
is the root directory where you are going to download and build NWChemEx.)

For the compute environment, we know that the following work:
* cmake: 3.9
* gcc: 6.2 or 6.3 or 7.10
* mpi: mpich 3.2
* doxygen: 1.8

If you are on a machine that uses modules, then it is recommended that you use those.

We use GitHub to manage the code.  See the [top level organization](https://github.com/NWChemEx-Project) 
to see all of the repositories.

There is a [short Git/GitHub tutorial](https://github.com/NWChemEx-Project/DeveloperDox/blob/master/README.md) 
that you should read if you are new to Git or GitHub.  It also includes some basic instructions on our workflow.

**Note:** The following optional command caches your GitHub username/password for 1 hour for convenience
```
git config --global credential.helper cache
```
Now you are ready to clone all of the repositories.  If you are going to just build and not
develop, then you can clone code from the NWChemEx-Project repositories.  If you are going
to make changes, it is recommended that you follow the [GitHub workflow](https://github.com/NWChemEx-Project/DeveloperDox/blob/master/README.md) instead (at least
for the part that you are going to change!).  An example of cloning directly from the
NWChemEx-Project repositories is:

```
git clone https://github.com/NWChemEx-Project/NWChemEx.git
cd NWChemEx
git clone https://github.com/NWChemEx-Project/NWChemExBase.git
git clone https://github.com/NWChemEx-Project/UtilitiesEx.git
git clone https://github.com/NWChemEx-Project/LibChemist.git
git clone https://github.com/NWChemEx-Project/IntegralsEx.git
git clone https://github.com/NWChemEx-Project/SCF.git
git clone https://github.com/NWChemEx-Project/DeveloperDox.git
```

[Basic instructions](https://github.com/NWChemEx-Project/NWChemExBase/blob/master/README.md) 
and [More detailed instructions](https://github.com/NWChemEx-Project/NWChemExBase/blob/master/dox/Building.md) for building with our cmake build.  However, explicit instructions are given below to help the
first time builder.

Currently, we need to build each of the repositories separately.  This will change once the 
repos go public since we will then be able to have the top level NWChemEx repo do all of the 
downloading and building. But for now, it is recommended that you build the repos in the 
following order and with the following commands:
```
cd $HOME/NWChemEx/NWChemExBase
cmake -H. -B$HOME/NWChemEx/NWChemExBase/build -DCMAKE_INSTALL_PREFIX=$HOME/NWChemEx/install -DBUILD_TESTS=false
```
(The last –D is so that it won’t try to build libint which is the test of the build framework.
If you want to test that the build system is working, go ahead and leave this final option off.
It may just take a bit of time to build.)
```
cd build
make
make install
ctest 
```
**Note:** Don't do this last step if you included the last -D option in the first cmake command!)
```
cd $HOME/NWChemEx/UtilitiesEx
cmake –H. –B$HOME/NWChemEx/UtilitiesEx/build –DCMAKE_INSTALL_PREFIX=$HOME/NWChemEx/install 
cd build
make
make install
ctest

cd $HOME/NWChemEx/LibChemist
cmake –H. –B$HOME/NWChemEx/LibChemist/build –DCMAKE_INSTALL_PREFIX=$HOME/NWChemEx/install 
cd build
make
make install
ctest

cd $HOME/NWChemEx/IntegralsEx
cmake –H. –B$HOME/NWChemEx/IntegralsEx/build –DCMAKE_INSTALL_PREFIX=$HOME/NWChemEx/install 
cd build
make
make install
ctest

cd $HOME/NWChemEx/SCF
cmake –H. –B$HOME/NWChemEx/SCF/build –DCMAKE_INSTALL_PREFIX=$HOME/NWChemEx/install 
cd build
make
make install
ctest
```
<!-- Need to update the TAMM build once we have the interface working -->
The TAMM code will also build with this same type of procedure.  However since it is currently not directly connected
to NWChemEx code, we delay this build.  We are still working on the interface of TAMM for our needs.

If you want to uninstall the code from the install directory (`$HOME/NWChemEx/install` in our examples), type `make uninstall`.

If you want to undo your build in any repo named `REPO`, the easiest thing to do is to
`rm -rf $HOME/NWChemEx/$REPO/build` and start again from the initial cmake command.  **Note:** If you want to
uninstall as well, you should `make uninstall` first and then remove the build directory.

If you would like to build the documentation:
```
cd $HOME/NWChemEx/DeveloperDox
doxygen dox/Doxyfile
```
The documentation will then be in the doc/html or doc/latex directories in that repo.
Note that you should also look at the [README](https://github.com/NWChemEx-Project/DeveloperDox/blob/master/dox/README.md) 
in the dox directory.  

You can do the same `doxygen dox/Doxyfile` command to build the documentation in 
each repo.  Eventually we will put together one cohesive set of documentation, but not until the repos
go public.