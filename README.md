# CRATOUS
CRoss-Application Translator for Operational Unmanned Systems
(CRATOUS) is a software bridge that enables the communication between
[UxAS](https://github.com/afrl-rq/OpenUxAS) and
[ICAROUS](https://github.com/nasa/icarous).

### License and Copyright Notice

The code in this repository is released under NASA's Open Source
Agreement.  See the directory [`LICENSE`](LICENSE).

<pre>

Notices:

Copyright 2018 United States Government as represented by the Administrator
of the National Aeronautics and Space Administration. All Rights Reserved.

Disclaimers:

No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY
OF ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT
LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO
SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE
SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF
PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN
ANY MANNER, CONSTITUTE AN ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR
RECIPIENT OF ANY RESULTS, RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR
ANY OTHER APPLICATIONS RESULTING FROM USE OF THE SUBJECT SOFTWARE. FURTHER,
GOVERNMENT AGENCY DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING
THIRD-PARTY SOFTWARE, IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES
IT "AS IS."

Waiver and Indemnity: RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS
ANY PRIOR RECIPIENT. IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS IN
ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH USE,
INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM, RECIPIENT'S
USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD HARMLESS THE
UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY
PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW. RECIPIENT'S SOLE REMEDY FOR
ANY SUCH MATTER SHALL BE THE IMMEDIATE, UNILATERAL TERMINATION OF THIS
AGREEMENT.

</pre>

---

## Installation Guide

### Requirement installation

(This was tested on an Ubuntu 32 bit system)

1. Install [UxAS](https://github.com/afrl-rq/OpenUxAS) and verify it is running correctly.
2. Switch to the ```ICAROUS_integration``` branch of UxAS and recompile UxAS.
3. Install [ICAROUS](https://github.com/nasa/icarous) and verify it is running correctly.
4. Switch ICAROUS branch to `cratous`:
```
git checkout cratous
```


### CRATOUS Installation
1. Copy the cratous repository into the `cFS/apps` folder relative to your ICAROUS installation with:

```
git clone http://github.com/nasa/cratous cFS/apps/cratous
```

2. Rebuild icarous from the top folder (icarous):

```
mkdir build
cd build
cmake -DCRATOUS=ON ..
make -j9 cpu1-install
```

3. At this point it should be good to run. To test, run the examples found in `OpenUxAS/example/07_.../`. The file `runDemo.sh` in each of these should run the example without any other input.
Note: You may need to set the value in `/proc/sys/fs/mqueue/max_msg` to `1000` so that ICAROUS can run without sudo.
