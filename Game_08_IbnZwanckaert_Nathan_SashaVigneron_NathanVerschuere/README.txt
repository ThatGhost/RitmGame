- Sasha Branch - 

-FrameWork Game_08-
-Ibn Zwanckaert-

--------------Input System-------------------

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

--------------UI System-------------------

void UIRectangle(Point2f Pos, Point2f Size, Color4f c);
-> draws a rectangle

void UITexture(Point2f Pos, Texture* t, const Rectf r = Rectf());
-> draws a texture

void UIElipse(Point2f Pos, Point2f Size, Color4f c);
-> draws an elipse

void UITriangle(Point2f Pos1, Point2f Pos2, Point2f Pos3, Color4f c);
-> draws a Triangle with the cornes on the points specified

bool UIButton(Point2f Pos, Point2f Size, Color4f c, bool Active = true);
-> draws a rectangle and returns true if pressed
-> default Active parameter controlls the state of the button (if it is able to be pressed)


bool UIButton(Point2f Pos, Texture* t, float scale, bool Active = true);
-> draws a texture and return true if pressed
-> default Active parameter controlls the state of the button (if it is able to be pressed)

--------------Save System-------------------

bool AddScore(int& score);
-> adds score to the right place and saves it
-> return true if new highscore

void InitializeGameAssets();
-> initialisez all the game assets
-> should never be used outside of start (game.cpp)

void DeleteGameAssets();
-> frees all the assets
-> should never be used outside of end (game.cpp)

std::vector<int> GetHighScores();
-> return a vector with all the highscores inside

void resetScore();
-> resets the highscores

--------------Texture System-------------------
Texture* GetTexture(const std::string& id);
-> return the texture specified by the id(name of file)

	example:
	DrawTexture(*GetTexture("Background.png"),Point2f(0,0));
	!!!! do not forget to put * infront of the GetTexture() !!!!

void FillText(std::string str, Point2f pos, int scale);
-> draws text at position, with scale (%)





