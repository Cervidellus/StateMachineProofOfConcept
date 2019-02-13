# StateMachineProofOfConcept
Developing a model hierarchical state machine for building automated hardware with distributed communication.
The intention is to have a central state machine node communicate to periperharal executables that perform services.
These services could be things like motion control, machine vision, imaging, input, etc.

The state machine is intended to be as simple as possible, and relies on the Qt state machine framework.
This framework makes it easy to create hierarchically ordered states, add transitions, and provide hooks to the GUI. 

Communication is done via zeroMQ via an XPUB/XSUB model. Using this setup, the communication could easily be converted to a conversation mode where the state machine could detect if a node crashed. 

The StateMachineZMQtest application allows you to walk through the state machine without connecting it to hardware by pushing buttons in the gui. 

The Messenger library handles all of the communications over ZMQ and can be included in any peripheral nodes.
