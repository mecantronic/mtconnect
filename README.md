# mtconnect

### structure
.
├── mtconnectApi1               -> first approach to take variable from mtconnect
│   ├── errorcheck.c            -> curl error check
│   ├── errorcheck.h
│   ├── mtconnectAPI.c          -> mtconnect file parser
│   ├── mtconnectAPITimed.sh    -> service launcher
│   ├── README.md
│   ├── transmition.c           -> upload program
│   └── transmitionTimed.sh     -> upload service launcher
└── mtconnectApi2               -> approach to take timestamp from windows shared folder
    ├── mtconnectApitxt.c       -> reads the windows file
    ├── mtconnectApitxt.sh      -> service launcher
    ├── README.md
    └── theMount.sh             -> windows folder mounter


Every program was compiled with:

gcc (Debian 12.2.0-14) 12.2.0
Copyright (C) 2022 Free Software Foundation, Inc.
