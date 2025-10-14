# Simple overlay loader
## How it works?
1.We allocate virtual memory PAGE_EXECUTE_READWRITE
2.We read file OVERLAY.BIN to this virtual memory and execute it
