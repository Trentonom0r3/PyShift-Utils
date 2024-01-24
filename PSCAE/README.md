# PSCAE
 Supplemental Library for PyShiftAE.

# Brief:
This Repo is to hold the supplemental library being built for PyShiftAE. This repo will most likely NOT have extensive documentation, as it is here mainly to keep things separated. 

# Main Points:
This is a work in progress. You cannot use this library without PyShiftAE, and even then, it doesn't quite work right with that yet either. 

- With the new approach, this module interracts with private IPC message queues set up in PyShiftAE, in order to script from external processes.
- Yes, I know what you're thinking.. 
    - "Does this mean I can script AE from outside of AE?"
        - While possible, this is designed for internal use only. Both for PyShiftAE's specific capabilities, and to more closely adhere to Adobe's policies. 

- Why?
- Why not?
    - Kidding. This opens up more realms of possibility. 
        - In being able to run separate python processes, users will have the ability to write a simple, custom `manifest.py` file, which will define their dependencies, resources, and main scripts. PyShiftAE will then set up each extension's environment, create menu commands for the extensions, and allow users to write extensions **FULLY** in python. Extensions can have varying dependencies due to the isolation.

# Main Issues:
- Intermittent usability:
    - I haven't found a solid "why" yet, but this will work for a few runs, and then run into a lot of hangs and stop working. 
        - Sometimes clearing AE cache and temp folder fixes this, other times I have to do that + rename the `Boost` message queues. 
    - My assumption would be some sort of synchronization issues.
        - I've already implemented singleton patterns in the MessageQueues, I think perhaps IPC mutexes would be the next step?