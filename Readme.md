Information courtesy of
IMDb
(http://www.imdb.com).
Used with permission.

Files

    buildidx.c
        Creates khs and vhs files from kv files
    key2val.c
        Given a key, this will produce a coresponding value
    val2key.c
        Given a value, this will produce a coresponding key
    actors
        Given a movie name, this will produce a list of actors who starred in it
    bacon1
        Given the name of an actor, this will produce a movie title in which that actor and Kevin Bacon were in the cast

Usage

    make all
        Compile all executables
    make util.o
        Create an object file for the util functions
    make hashfn.o
        Create an object file for the hashfn functions
    make buildidx
        Create an executable, buildidx
    make key2val
        Create an executable, key2val
    make val2key
        Create an executable, val2key
    make actors
        Create an executable, actors
    make bacon1
        Create an executable, bacon1
