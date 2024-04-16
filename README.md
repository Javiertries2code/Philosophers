As for last best idea

The thread monitor should
create dead status

minotor should loop along all thread  time left.

    LOCKs status[i]    
    if status [i] != FULL, *checking alive wouldnt make sense
   {
    
        CHECK TIME LEFT[i]; no  need of locking .
            if ( time left == 0) 
            {  chnage status = [all] = DIED; looping
        UNLOCK status;
        lock write
            write death
        unlock
        RETURN;}
    }
        else if status [i] == FULL
        UNLOCK stauts[i];
        i++;


create var

thinking->eating- sleeping


if(max_meals <= 0)
    Lock status
        status = FULL;
    unlock status:
    return FULL
    

    In the THREAD
    LOCK WRITE;
        LOCK STATUS;
        var = status
            if(!= 0)
                RETURN STATUS
            write ACTION
        UNLOCK STATUS
    UNLOCK WRITE
    if status 