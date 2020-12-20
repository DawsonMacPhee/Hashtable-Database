Information courtesy of IMDb (http://www.imdb.com). Used with permission.
This project makes use of three kv files which hold information about movies from the IMDB database.
The given main functions perform different types of searches and references to the data.

Files

    buildidx.c
        Creates khs and vhs files from kv files
        This is what creates the database from the kv files
        
    key2val.c
        Given a key, this will produce a coresponding value
        
    val2key.c
        Given a value, this will produce a coresponding key
        
    actors
        Given a movie name, this will produce a list of actors who starred in it
        
    bacon1
        Given the name of an actor, this will produce a movie title in which that actor and Kevin Bacon were in the cast
        

Usage (make)

    all
        Compiles all the main functions for the project
        
    util.o
        Create an object file for the util functions
        
    hashfn.o
        Create an object file for the hashfn functions
        
    buildidx.o
        Creates the object file buildidx.o
        
    key2val.o
        Creates the object file key2val.o
        
    val2key.o
        Creates the object file val2key.o
        
    actors.o
        Creates the object file actors.o
        
    bacon1.o
        Creates the object file bacon1.o
        
    buildidx
        Create the executable buildidx
        
    key2val
        Create the executable key2val
        
    val2key
        Create the executable val2key
        
    actors
        Create the executable actors
        
    bacon1
        Create the executable bacon1
        
    clean
        Removes the object files and executables
        
