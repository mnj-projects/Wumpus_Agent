# Wumpus Game - Intelligent Agent

This project tries to create and develop an agent which can play the 1972 developed "Hunt the Wumpus" game. This project has two major components: the game and the intelligent agent. 

In order to introduce predictability to the agent we have added constraints to the environment. 

- The game uses a 4x4 box
- Adjacent rooms are all OK
- Indefinite states are not handled.

The agent tries to do most of its traversal of the environment primarily by going to OK rooms (OK driven). When no OK rooms are left it will attempt to kill the Wumpus to check rooms that might be blocked by the monster.



### Vocabulary

B <sub>i j</sub>	- Breeze in room i,j

S <sub>i j</sub>	- Stench in room i,j

G <sub>i j</sub>	- Glitter in room i,j

OK <sub>i j</sub>	-  No threats in room i,j

V <sub>i j</sub>	- Room i,j has been visited

P <sub>i j</sub>	- Pit in room i,j

W <sub>i j</sub>	- Wumpus in room i,j



The agent uses these sematic tableaux rules in order to mechanize its actions within the environment. 

#### OK Room Check

If there is no stench or no breeze ⊨ All adjacent rooms are OK

##### 		¬S<sub>i j</sub> , ¬B<sub>i j</sub>	⊨	(OK<sub>i j+1</sub> ∧ OK<sub>i j-1</sub> ∧ OK<sub>i+1 j</sub> ∧ OK<sub>i-1 j</sub> )



WPP(i,j) equals 0 and 1 at the same time => The WPP(i,j) is safe

##### 		WPP <sub>i j</sub> ,	¬WPP <sub>i j</sub> <sup>'</sup>	⊨	¬W<sub>i j</sub> 



PPP(i,j) equals 0 and 1 at the same time => The PPP(i,j) is safe

##### 		PPP <sub>i j</sub> ,	¬PPP <sub>i j</sub> <sup>'</sup>	⊨	¬P<sub>i j</sub>

##### 		WPP <sub>i j</sub> ,	WPP <sub>i j</sub><sup>'</sup>,	PPP <sub>i j</sub> ,	PPP <sub>i j</sub> <sup>'</sup>	⊨	OK<sub>i j</sub>



#### Wumpus Check using Stench

Two WPP(i,j) means a Wumpus is there

##### 		WPP <sub>i j</sub> , ¬WPP <sub>i j</sub> <sup>'</sup>	⊨	W<sub>i j</sub>



Two (or three) adjacent sides of S(i,j) are not W(i,j)

##### 		S <sub>i j</sub> ,	( ¬W <sub>i j+1</sub>	∧	¬W <sub>i j-1</sub>	∧	¬W <sub>i+1 j</sub> )	⊨	¬W <sub>i-1 j</sub>

##### 		S <sub>i j</sub> ,	( ¬W <sub>i j+1</sub>	∧	¬W <sub>i j-1</sub>	∧	¬W <sub>i-1 j</sub> )	⊨	¬W <sub>i+1 j</sub>

##### 		S <sub>i j</sub> ,	( ¬W <sub>i j-1</sub>	∧	¬W <sub>i+1 j</sub>	∧	¬W <sub>i-1 j</sub> )	⊨	¬W <sub>i j+1</sub>

##### 		S <sub>i j</sub> ,	( ¬W <sub>i j+1</sub>	∧	¬W <sub>i+1 j</sub>	∧	¬W <sub>i-1 j</sub> )	⊨	¬W <sub>i j-1</sub>



Two S(i,j) and one of their common adjacent room is NOT W(i,j)



#### Pit Check using Breeze

Two (or three) adjacent sides of B(i,j) are not P(i,j). This follows the same reasoning as the wumpus check. 

#####     B <sub>i j</sub> ,	( ¬P <sub>i j+1</sub>	∧	¬P <sub>i j-1</sub>	∧	¬P <sub>i+1 j</sub> )	⊨	¬P <sub>i-1 j</sub>

##### 		B <sub>i j</sub> ,	( ¬P <sub>i j+1</sub>	∧	¬P <sub>i j-1</sub>	∧	¬P <sub>i-1 j</sub> )	⊨	¬P <sub>i+1 j</sub>

##### 		B <sub>i j</sub> ,	( ¬P <sub>i j-1</sub>	∧	¬P <sub>i+1 j</sub>	∧	¬P <sub>i-1 j</sub> )	⊨	¬P <sub>i j+1</sub>

##### 		B <sub>i j</sub> ,	( ¬P <sub>i j+1</sub>	∧	¬P <sub>i+1 j</sub>	∧	¬P <sub>i-1 j</sub> )	⊨	¬P <sub>i j-1</sub>

 

Two B(i,j) and one of their common adjacent room is NOT P(i,j)



**Note**: NOT W(i,j) and NOT P(i,j) means that the room is anything but those things. This means it can be OK, V, G, W (or P, depending).	If it is one of those things it categorizes as NOT P(i,j) OR W(i,j)

¬W<sub>i j</sub> = OK<sub>i j</sub>	||	V<sub>i j</sub>	||	G<sub>i j</sub>	||	P<sub>i j</sub>

¬P<sub>i j</sub> = OK<sub>i j</sub>	||	V<sub>i j</sub>	||	G<sub>i j</sub>	||	W<sub>i j</sub>



