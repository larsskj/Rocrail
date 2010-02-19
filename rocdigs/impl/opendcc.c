/** ------------------------------------------------------------
  * A U T O   G E N E R A T E D  (First time only!)
  * Generator: Rocs ogen (build Nov  9 2006 08:04:42)
  * Module: RocDigs
  * XML: $Source: /cvsroot/rojav/rocdigs/rocdigs.xml,v $
  * XML: $Revision: 1.14 $
  * Object: OpenDCC
  * Date: Mon Mar  3 17:05:53 2008
  * ------------------------------------------------------------
  * $Source$
  * $Author$
  * $Date$
  * $Revision$
  * $Name$
  */

#include "rocdigs/impl/opendcc_impl.h"

#include "rocint/public/digint.h"

#include "rocrail/wrapper/public/DigInt.h"
#include "rocrail/wrapper/public/OpenDCC.h"
#include "rocrail/wrapper/public/Program.h"
#include "rocrail/wrapper/public/BinCmd.h"
#include "rocrail/wrapper/public/Response.h"
#include "rocrail/wrapper/public/Switch.h"
#include "rocrail/wrapper/public/Loc.h"
#include "rocrail/wrapper/public/SysCmd.h"
#include "rocrail/wrapper/public/Clock.h"

#include "rocs/public/mem.h"
#include "rocs/public/lib.h"
#include "rocs/public/system.h"

#include <time.h>

static int instCnt = 0;

/** ----- OBase ----- */
static const char* __id( void* inst ) {
  return NULL;
}

static void* __event( void* inst, const void* evt ) {
  return NULL;
}

static void __del( void* inst ) {
  if( inst != NULL ) {
    iOOpenDCCData data = Data(inst);
    /* Cleanup data->xxx members...*/

    freeMem( data );
    freeMem( inst );
    instCnt--;
  }
  return;
}

static const char* __name( void ) {
  return name;
}

static unsigned char* __serialize( void* inst, long* size ) {
  return NULL;
}

static void __deserialize( void* inst,unsigned char* bytestream ) {
  return;
}

static char* __toString( void* inst ) {
  return NULL;
}

static int __count( void ) {
  return instCnt;
}

static struct OBase* __clone( void* inst ) {
  return NULL;
}

static Boolean __equals( void* inst1, void* inst2 ) {
  return False;
}

static void* __properties( void* inst ) {
  iOOpenDCCData data = Data(inst);
  return data->ini;
}

/** ----- OOpenDCC ----- */


/**  */
static iONode _cmd( obj inst ,const iONode cmd ) {
  iOOpenDCCData data = Data(inst);
  iONode response = NULL;

  /* TODO: check for OpenDCC specific commands like programming the CS
   * and make bincmd's for the p50x
   * wProgram.getlntype == wProgram.lntype_cs
   * wProgram.getcmd == wProgram.get or wProgram.set
   * wProgram.getcv  -> SO register
   * wProgram.getval -> SO value
   *  */

  /* Clock command. */
  if( StrOp.equals( NodeOp.getName( cmd ), wClock.name() ) && wOpenDCC.isfastclock( data->opendccini ) ) {
    /*
    # XClkSet (0xC0) - Length = 5 Bytes

    command bytes:
    0: 0xC0 XClkSet: fast clock
    1: TCODE0: 00mmmmmm, this denotes the minute, range 0..59.
    2: TCODE1: 100HHHHH, this denotes the hour, range 0..23
    3: TCODE2: 01000WWW, this denotes the day of week,
    0=Monday, 1=Tuesday, 2=Wednesday, 3=Thursday, 4=Friday, 5=Saturday, 6=Sunday.
    4: TCODE3: 110FFFFF, this denotes the acceleration factor, range 0..31;
    an acceleration factor of 0 means clock is stopped,
    a factor of 1 means clock is running real time,
    a factor of 2 means clock is running twice as fast a real time.

    Answer: 0 (Kommando okay)
    */
    iONode clockcmd = NodeOp.inst( wBinCmd.name(), NULL, ELEMENT_NODE );
    char* byteStr = NULL;
    byte outBytes[6];
    long l_time = wClock.gettime(cmd);
    struct tm* lTime = localtime( &l_time );

    int mins    = lTime->tm_min;
    int hours   = lTime->tm_hour;
    int wday    = lTime->tm_wday;
    int divider = wClock.getdivider(cmd);

    TraceOp.trc( name, TRCLEVEL_DEBUG, __LINE__, 9999,
        "%s clock to %02d:%02d divider=%d", wClock.getcmd( cmd ), hours, mins, divider );

    if( StrOp.equals( wDigInt.p50x, data->sublibname )  && StrOp.equals( wClock.set, wClock.getcmd( cmd ) ) ) {
      outBytes[0] = (byte)'x';
      outBytes[1] = 0xC0;
      outBytes[2] = 0x00 + mins;
      outBytes[3] = 0x80 + hours;
      outBytes[4] = 0x40 + wday;
      outBytes[5] = 0xC0 + divider;

      byteStr = StrOp.byteToStr( outBytes, 6 );
      wBinCmd.setoutlen( clockcmd, 6 );
      wBinCmd.setinlen( clockcmd, 1 );
      wBinCmd.setout( clockcmd, byteStr );
      StrOp.free( byteStr );
      response = data->sublib->cmd((obj)data->sublib, clockcmd);
    }
    else {
      /* the lenz protocol knows the clock command */
      response = data->sublib->cmd((obj)data->sublib, cmd);
    }

  }

  /* Program command. */
  else if( StrOp.equals( NodeOp.getName( cmd ), wProgram.name() ) &&
      wProgram.getlntype( cmd ) == wProgram.lntype_cs )
  {
    iONode ptcmd = NULL;
    Boolean getCV = False;

    if(  wProgram.getcmd( cmd ) == wProgram.set ) {
      if( StrOp.equals( wDigInt.p50x, data->sublibname ) ) {
        ptcmd = NodeOp.inst( wBinCmd.name(), NULL, ELEMENT_NODE );
        char* byteStr = NULL;
        byte outBytes[6];
        outBytes[0] = (byte)'x';
        outBytes[1] = 0xA3;
        outBytes[2] = wProgram.getcv(cmd) % 256;
        outBytes[3] = wProgram.getcv(cmd) / 256;
        outBytes[4] = wProgram.getvalue(cmd);

        byteStr = StrOp.byteToStr( outBytes, 5 );
        wBinCmd.setoutlen( ptcmd, 5 );
        wBinCmd.setinlen( ptcmd, 1 );
        wBinCmd.setout( ptcmd, byteStr );
        StrOp.free( byteStr );
      }
      else {
        /* lenz sublib
           0x24 0x29 AddrH AddrL DAT [XOR]
           SO write request. The answer is 0x24 0x28 AddrH AddrL DATA [XOR]
        */
        ptcmd = NodeOp.inst( wBinCmd.name(), NULL, ELEMENT_NODE );
        char* byteStr = NULL;
        byte outBytes[6];
        outBytes[0] = 0x24;
        outBytes[1] = 0x29;
        outBytes[2] = wProgram.getcv(cmd) / 256;
        outBytes[3] = wProgram.getcv(cmd) % 256;
        outBytes[4] = wProgram.getvalue(cmd);

        byte bXor = 0;
        int i = 0;
        for( i = 0; i < 5; i++ ) {
          bXor ^= outBytes[ i ];
        }
        outBytes[5] = bXor;

        byteStr = StrOp.byteToStr( outBytes, 6 );
        wBinCmd.setoutlen( ptcmd, 6 );
        wBinCmd.setinlen( ptcmd, 6 );
        wBinCmd.setout( ptcmd, byteStr );
        StrOp.free( byteStr );

      }
    }
    else if(  wProgram.getcmd( cmd ) == wProgram.get ) {
      if( StrOp.equals( wDigInt.p50x, data->sublibname ) ) {
        ptcmd = NodeOp.inst( wBinCmd.name(), NULL, ELEMENT_NODE );
        char* byteStr = NULL;
        byte outBytes[4];
        outBytes[0] = (byte)'x';
        outBytes[1] = 0xA4;
        outBytes[2] = wProgram.getcv(cmd) % 256;
        outBytes[3] = wProgram.getcv(cmd) / 256;

        byteStr = StrOp.byteToStr( outBytes, 4 );
        wBinCmd.setoutlen( ptcmd, 4 );
        wBinCmd.setinlen( ptcmd, 2 );
        wBinCmd.setout( ptcmd, byteStr );
        StrOp.free( byteStr );

        getCV = True;
      }
      else {
        /* lenz sublib
           0x23 0x28 AddrH AddrL [XOR]
           SO (special option) read request; this allows to read the internal configuration values.
           AddrH AddrL denotes the address of the CV.
           The answer is 0x24 0x28 AddrH AddrL DATA [XOR]
         */
        ptcmd = NodeOp.inst( wBinCmd.name(), NULL, ELEMENT_NODE );
        char* byteStr = NULL;
        byte outBytes[5];
        outBytes[0] = 0x23;
        outBytes[1] = 0x28;
        outBytes[2] = wProgram.getcv(cmd) / 256;
        outBytes[3] = wProgram.getcv(cmd) % 256;

        byte bXor = 0;
        int i = 0;
        for( i = 0; i < 4; i++ ) {
          bXor ^= outBytes[ i ];
        }
        outBytes[4] = bXor;

        byteStr = StrOp.byteToStr( outBytes, 5 );
        wBinCmd.setoutlen( ptcmd, 5 );
        wBinCmd.setinlen( ptcmd, 6 );
        wBinCmd.setout( ptcmd, byteStr );
        StrOp.free( byteStr );

        getCV = True;
      }
    }

    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999,
        "XSO%s for register %d", (getCV?"Get":"Set"), wProgram.getcv(cmd) );


    if( ptcmd != NULL ) {
      byte* inData = NULL;
      response = data->sublib->cmd((obj)data->sublib, ptcmd);
      /* TODO: convert response incase of a bincmd */
      inData = StrOp.strToByte( wResponse.getdata( response ) );
      NodeOp.base.del(response);
      response = (iONode)NodeOp.base.clone(cmd);
      if( getCV && inData[0] == 0 ) {
        wProgram.setvalue( response, inData[1] );
        wOpenDCC.setlib( response, wOpenDCC.getlib(data->opendccini) );
        TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999,
            "Successfully XSO%s [%d][%d]", (getCV?"Get":"Set"), wProgram.getcv(cmd), inData[1] );
      }
      else if( inData[0] != 0 ) {
        /* Error PT command */
        TraceOp.trc( name, TRCLEVEL_WARNING, __LINE__, 9999,
            "Error [%s] XSO%d [%d]", (getCV?"Get":"Set"), inData[0], wProgram.getcv(response) );
      }
      freeMem(inData);
    }

    /* Cleanup command node */
    NodeOp.base.del(cmd);
  }
  else if( StrOp.equals( NodeOp.getName( cmd ), wSwitch.name() ) ) {
    /* OpenDCC does not switch off the gate */
    iONode cmdoff = (iONode)NodeOp.base.clone(cmd);
    int swtime = wSwitch.getdelay(cmd);
    if( swtime == 0 )
      swtime = wDigInt.getswtime(data->ini);
    response = data->sublib->cmd((obj)data->sublib, cmd);

    if( swtime > 0 ) {
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "posting to switch delay thread" );
      wSwitch.setdelay( cmdoff, swtime );
      wSwitch.setdelaytime( cmdoff, SystemOp.getMillis() );
      ThreadOp.post( data->swdelay, (obj)cmdoff );
    }
    else {
      /* free up the unused node */
      NodeOp.base.del(cmdoff);
    }
  }
  else if( StrOp.equals( NodeOp.getName( cmd ), wLoc.name() ) ) {
    if( StrOp.equals( wLoc.shortid, wLoc.getcmd(cmd) ) ) {
      TraceOp.trc( name, TRCLEVEL_MONITOR, __LINE__, 9999,
          "addr=%d spcnt=%d shortID=[%s]", wLoc.getaddr(cmd), wLoc.getspcnt(cmd), wLoc.getshortid(cmd) );
      /* send short ID to OpenDCC */
      if( StrOp.equals( wDigInt.p50x, data->sublibname ) ) {
        /* add the loco to the data bank, or overwrite the existing */
        iONode lccmd = NodeOp.inst( wBinCmd.name(), NULL, ELEMENT_NODE );
        char* str = StrOp.fmt( "x LOCADD %d,%d,DCC,%s\r", wLoc.getaddr(cmd), wLoc.getspcnt(cmd), wLoc.getshortid(cmd) );
        char* byteStr = StrOp.byteToStr( str, StrOp.len(str) );
        wBinCmd.setoutlen( lccmd, StrOp.len(byteStr) );
        wBinCmd.setinlen( lccmd, 0 );
        wBinCmd.setout( lccmd, byteStr );
        StrOp.free( byteStr );
        StrOp.free( str );
        response = data->sublib->cmd((obj)data->sublib, lccmd);
      }
      else {
        /* lenz sublib */
      }
    }
    else {
      response = data->sublib->cmd((obj)data->sublib, cmd);
    }
  }
  else if( StrOp.equals( NodeOp.getName( cmd ), wSysCmd.name() ) ) {
    if( StrOp.equals( wSysCmd.txshortids, wSysCmd.getcmd(cmd) ) ) {
      TraceOp.trc( name, TRCLEVEL_MONITOR, __LINE__, 9999, "send short IDs to the throttle" );
      if( StrOp.equals( wDigInt.p50x, data->sublibname ) ) {
        /* dump the loco data base in the throttle */
        iONode lccmd = NodeOp.inst( wBinCmd.name(), NULL, ELEMENT_NODE );
        char* byteStr = StrOp.byteToStr( "x LOCXMT\r", StrOp.len("x LOCXMT\r") );
        wBinCmd.setoutlen( lccmd, StrOp.len(byteStr) );
        wBinCmd.setinlen( lccmd, 0 );
        wBinCmd.setout( lccmd, byteStr );
        StrOp.free( byteStr );
        response = data->sublib->cmd((obj)data->sublib, lccmd);
      }
      else {
        /* lenz sublib */
      }
    }
    else {
      response = data->sublib->cmd((obj)data->sublib, cmd);
    }
  }
  else {
    response = data->sublib->cmd((obj)data->sublib, cmd);
  }




  return response;
}


/**  */
static void _halt( obj inst ) {
  iOOpenDCCData data = Data(inst);
  data->run = False;
  data->sublib->halt((obj)data->sublib);
  return;
}


/**  */
static Boolean _setListener( obj inst ,obj listenerObj ,const digint_listener listenerFun ) {
  iOOpenDCCData data = Data(inst);
  return data->sublib->setListener( (obj)data->sublib , listenerObj, listenerFun );
}


/** bit0=power, bit1=programming, bit2=connection */
static int _state( obj inst ) {
  iOOpenDCCData data = Data(inst);
  return data->sublib->state((obj)data->sublib);
}


/* external shortcut event */
static void _shortcut(obj inst) {
  iOOpenDCCData data = Data( inst );
}


/**  */
static Boolean _supportPT( obj inst ) {
  iOOpenDCCData data = Data(inst);
  return data->sublib->supportPT((obj)data->sublib);
}


static void __swdelayThread( void* threadinst ) {
  iOThread th = (iOThread)threadinst;
  iOOpenDCC opendcc = (iOOpenDCC)ThreadOp.getParm( th );
  iOOpenDCCData data = Data(opendcc);
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "OpenDCC switch delay thread started." );

  while( data->run ) {
    obj post = ThreadOp.getPost( th );
    if( post != NULL ) {
      iONode cmdoff = (iONode)post;
      long delaytime = wSwitch.getdelaytime( cmdoff );
      if( SystemOp.getMillis() - wSwitch.getdelay(cmdoff) > 0 ) {
        /* sleep the delay in ms */
        ThreadOp.sleep(SystemOp.getMillis() - wSwitch.getdelay(cmdoff));
      }
      /* deactovate the output */
      wSwitch.setactivate(cmdoff, False );
      data->sublib->cmd((obj)data->sublib, cmdoff);
    }
    else {
      ThreadOp.sleep(10);
    }

  }

  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "OpenDCC switch delay thread ended." );
}


/* VERSION: */
static int vmajor = 1;
static int vminor = 4;
static int patch  = 0;
static int _version( obj inst ) {
  iOOpenDCCData data = Data(inst);
  return vmajor*10000 + vminor*100 + patch;
}


typedef iIDigInt (* LPFNROCGETDIGINT)( const iONode ,const iOTrace );

/**  */
static struct OOpenDCC* _inst( const iONode ini ,const iOTrace trc ) {
  iOOpenDCC __OpenDCC = allocMem( sizeof( struct OOpenDCC ) );
  iOOpenDCCData data = allocMem( sizeof( struct OOpenDCCData ) );
  MemOp.basecpy( __OpenDCC, &OpenDCCOp, 0, sizeof( struct OOpenDCC ), data );

  /* Initialize data->xxx members... */
  TraceOp.set( trc );

  data->ini = ini;
  data->opendccini = wDigInt.getopendcc(ini);
  data->iid        = StrOp.dup( wDigInt.getiid( ini ) );

  if( data->opendccini == NULL )
    data->opendccini = NodeOp.inst( wOpenDCC.name(), ini, ELEMENT_NODE );

  data->sublibname = StrOp.dup( wOpenDCC.getlib( data->opendccini ) );

  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "----------------------------------------" );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "opendcc %d.%d.%d", vmajor, vminor, patch );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "iid    = %s", data->iid );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "sublib = %s", data->sublibname );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "----------------------------------------" );

  /* load sub library */
  {
    iOLib    pLib = NULL;
    LPFNROCGETDIGINT pInitFun = (void *) NULL;
    /* TODO: get the library path! */
    char* libpath = StrOp.fmt( "%s%c%s", wDigInt.getlibpath(data->ini),
        SystemOp.getFileSeparator(), data->sublibname );
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "try to load [%s]", libpath );
    pLib = LibOp.inst( libpath );
    StrOp.free( libpath );


    if (pLib != NULL) {
      pInitFun = (LPFNROCGETDIGINT)LibOp.getProc(pLib,"rocGetDigInt");
      if (pInitFun != NULL) {
        data->sublib = pInitFun( ini, trc );
      }
    }
  }

  if( data->sublib == NULL ) {
    TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "unable to load [%s]", wOpenDCC.getlib( data->opendccini ) );
    freeMem( data );
    freeMem(__OpenDCC);
    return NULL;
  }

  data->run = True;

  data->swdelay = ThreadOp.inst( "swdelay", &__swdelayThread, __OpenDCC );
  ThreadOp.start( data->swdelay );


  instCnt++;
  return __OpenDCC;
}

/* Support for dynamic Loading */
iIDigInt rocGetDigInt( const iONode ini ,const iOTrace trc )
{
  return (iIDigInt)_inst(ini,trc);
}


/* ----- DO NOT REMOVE OR EDIT THIS INCLUDE LINE! -----*/
#include "rocdigs/impl/opendcc.fm"
/* ----- DO NOT REMOVE OR EDIT THIS INCLUDE LINE! -----*/
