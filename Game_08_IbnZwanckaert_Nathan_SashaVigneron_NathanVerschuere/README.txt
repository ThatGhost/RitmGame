-FrameWork v2 Input rework-
-Ibn Zwanckaert-

To call an input you type:
Input

--Diffrent types of Input:--

-KeyDown & KeyUp:

you check the currently pressed key by typing Input.KeyDown 
and then checking what key you want to interact with.
The same principle is used with Up.
Example:

if (Input.keyDown == 'g')
{
	//some code
}

or 

if (Input.keyUp == SDLK_g)
{
	//some code
}

-MousePosition

you check the mouse x and y position in the box by typing:
Input.mousePos(.x)(.y)
Example:

if(Input.mousePos.x > 50)
{
	//some code
}

-MouseDown && MouseUp

You check the current pressed mouse by typing:
Input.ClickDown.
This can have either of 3 states:
MB1 (left click), MB2 (Middle click) or MB3 (Right click)
Example:

if (Input.ClickDown == Input.MB1)
{
	//some code
}

or

if (Input.ClickUp == Input.MB3)
{
	//some code
}