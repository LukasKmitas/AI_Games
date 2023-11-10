# Lab 6

Num keys (1-5) to toggle Text display
1 - To see what Number the tile is.
2 - This is to see the Tile cost.
3 - This is to see the integrationF cost.
4 - This is to see the Path from Start Tile to End (Goal) Tile.
5 - Toggle to use the Vector Path or FlowField Path.

EXTRA - Agent (NPC) that follows the path from Start Tile to the End tile (Goal)
	It also has a shader pretty cool.
	Gradient color for the Vector field.


NOTE: 
	Depending on what computer you use the text or window screen can change sizes,
	You can change these in:
	Global.h - to change the size of screen it NEEDS to devide by 50 to fit.
	Grid.cpp - Line 166 to change the text size.
	Agent (NPC) - Line 59 inside setupAgent() set radius, how big is the agent.
