# Upstream information

eCoinCore upstream: Canada eCoin Core,  https://github.com/canada-ecoin/ecoincore  

The Canada eCoin project uses resources from other active projects.  This makes it easier for us to stay up to date and utilize development activities from all around this space.


# Current streams

Here is a list of the sections that make up the Canada eCoin and where the upstream is located.


## Building

The build system is deterministic and should be used solely to build the Canada eCoin Core repo.  

the depends folder is use to house the build enviroment.  

using these build tools you will  

1. download the source and perfom the compilations of all the dependancies needed all using automake
	- please report any errors here.  there should be none.  

to prepare the build enviroment for your current system.  
```  
cd depends
make
```

it is possible to cross compile (compile on one system for use on another) but that is beyond the scope of this document, check /depends/README.md for more information.  
