
//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;


//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *dot = NULL;
SDL_Surface *normal_platform = NULL;
SDL_Surface *fake_platform_1 = NULL;
SDL_Surface *fake_platform_2 = NULL;
SDL_Surface *fake_platform_3 = NULL;
SDL_Surface *fake_platform_4 = NULL;
SDL_Surface *moving_side_to_side_platform = NULL;
SDL_Surface *disappearing_platform_1 = NULL;
SDL_Surface *disappearing_platform_2 = NULL;
SDL_Surface *explosive_red_platform = NULL;
SDL_Surface *explosive_yellow_platform = NULL;
SDL_Surface *exploded_platform = NULL;
SDL_Surface *spring_rest = NULL;
SDL_Surface *spring_stretched = NULL;
SDL_Surface *trampolin_f1 = NULL;
SDL_Surface *trampolin_f2 = NULL;
SDL_Surface *trampolin_f3 = NULL;
SDL_Surface *jetpack = NULL;
SDL_Surface *black_hole = NULL;
SDL_Surface *Score = NULL;
SDL_Surface *HiScore = NULL;
SDL_Surface *dotr = NULL;
SDL_Surface *dotl = NULL;
SDL_Surface *dotu = NULL;
SDL_Surface *play_button = NULL;
SDL_Surface *menu_back = NULL;
SDL_Surface *pause_back = NULL;
SDL_Surface *resume_button = NULL;
SDL_Surface *pause_button = NULL;
SDL_Surface *menu_button = NULL;
SDL_Surface *game_over = NULL;
SDL_Surface *playagain = NULL;

Mix_Chunk *tramp = NULL;
Mix_Chunk *springs = NULL;
Mix_Chunk *over = NULL;
Mix_Chunk *explo = NULL;
Mix_Chunk *platforms = NULL;
Mix_Chunk *breaks = NULL;


const int FRAMES_PER_SECOND = 20;


const int n=10;
const double Vx = 2;
//const double Vy = 2;

//The event structure
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

struct Dot
{
    int x, y;

    int width;

    int height;

    int xVel, yVel;

    void handle_input(bool &play , bool &pause , double &pause_x , double &pause_y , int &pause_h , int &pause_w );

    void move(bool &play , bool &gameover);

};

struct Timer
{
    int startTicks;
    int pausedTicks;

    bool paused;
    bool started;

    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_started();
    bool is_paused();
};

struct platform
{
	public:

	int state;

	int height;
	int width ;

	double x;
	double y;

	double Vx;
	//double Vy;

	string type;

	bool display;

};

struct spring
{
	double x;

	double y;

	double Vx;

	int height;

	int width;

	int leftd;

	int rightd;

	bool display;

	string state;
	
};


struct trampolin
{
	double x;

	double y;

	double Vx;

	int height;

	int width;

	int leftd;

	int rightd;

	bool display;

	string state;


};


struct jetpack
{
	double x;

	double y;

	double Vx;

	int height;

	int width;

	int leftd;

	int rightd;

	bool display;

	int state;

};


struct monster
{
	double x;

	double y;

	double Vx;

	int height;

	int width;

	bool display;

	string state;

};


struct blackhole
{
	double x;

	double y;

	int height;

	int width;

	bool display;

};


SDL_Surface *load_image( string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        /*//If the surface was optimized
        if( optimizedImage != NULL )
        {
        	//Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
            //Color key surface
            //SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        } */
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}


void pause_menu( bool &pause , bool &play )
{
	// PAUSE BUTTON DIMENTION
	int p_h = 62;
	int p_w = 170;
	int p_x = 30;
	int p_y = 400;

	//The mouse offsets
    int x = 0, y = 0;

	while( pause )
	{
		// DISPLAY BACKGROUND
		apply_surface( 0, 40, pause_back, screen);

		// DISPLAY RESUME BUTTON
		apply_surface( p_x, p_y, resume_button , screen);

		while ( SDL_PollEvent( &event ) )
		{
		
			if( event.type == SDL_MOUSEBUTTONDOWN )
    		{
        		//If the left mouse button was pressed
        		if( event.button.button == SDL_BUTTON_LEFT )
        		{
            		//Get the mouse offsets
            		x = event.button.x;
            		y = event.button.y;
        
            		if( (x>p_x) && (x<p_x + p_w) && (y>p_y) && (y<p_y + p_h) )
            		{
        						pause = false;

        			}

            	}
            }
        	//If the user has Xed out the window
        	else if( event.type == SDL_QUIT )
        	{
            	//Quit the program
            	pause = false;
            	play = false;

        	}

        

        	if( SDL_Flip( screen ) == -1 )
			{
				pause = false;
				play = false;
			}

		}
    }

	

}

void Dot::handle_input( bool &play , bool &pause , double &pause_x , double &pause_y , int &pause_h , int &pause_w )
{
	int t = 25;

	//The mouse offsets
    int x = 0, y = 0;

	while( SDL_PollEvent( &event ) )
	{
    	//If a key was pressed
    	if( event.type == SDL_KEYDOWN )
    	{
        	//Adjust the velocity
        	switch( event.key.keysym.sym )
        	{
            	case SDLK_LEFT: {
                	xVel -= t;
                	dot = dotl;
                 	break;}
            
            	case SDLK_RIGHT: {
                	xVel += t; 
                	dot = dotr;
                	break;}

            	case SDLK_SPACE: { 
                	dot = dotu;
                	break;}
        	}
    	}
    	//If a key was released
    	else if( event.type == SDL_KEYUP )
    	{
        	//Adjust the velocity
        	switch( event.key.keysym.sym )
        	{
            	case SDLK_LEFT: xVel += t; break;
            	case SDLK_RIGHT: xVel -= t; break;
            	case SDLK_SPACE: { 
                	dot = load_image( "Doodler6060r.png" );
                	break;}
        	}
    	}
    	else if( event.type == SDL_QUIT )
        	{
            	//Quit the program
            	play = false;
        	}
        else if( event.type == SDL_MOUSEBUTTONDOWN )
    	{
        		//If the left mouse button was pressed
        		if( event.button.button == SDL_BUTTON_LEFT )
        		{
            		//Get the mouse offsets
            		x = event.button.x;
            		y = event.button.y;
        
            		if( (x>pause_x) && (x<pause_x + pause_w) && (y>pause_y) && (y<pause_y + pause_h) )
            		{
        						pause = true;

        						pause_menu( pause , play );
        			}

            	}
        }	
	}
}

void Dot::move( bool &play , bool &gameover )
{

    //Move the dot left or right
    x += xVel;

    //If the dot went too far to the left or right
    if (x  > 350 ){
       x=0; 
    } 

   else if( ( x < 0 ) ){
        x=350;
    }
    
    yVel--;
    y-=yVel; 

    if( y>SCREEN_HEIGHT )
    	{
    		play = false;

    		gameover = true;

    	}
 
    
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int space_counter=0;
int counter;

void generate( platform &p, platform &pa, platform &pb, spring &spr, trampolin &trm , blackhole &blh ,int &score , int &count , double &distance, int Vy )
{	
	int type;
	int w=130;
	
	if(p.y-(pa.y+Vy)<40){
		
		do {
			p.x = rand()%(SCREEN_WIDTH - p.width);
		} while (p.x+w<=pa.x || p.x>=pa.x+w);

	
	}

	else {
		p.x = rand()%(SCREEN_WIDTH - p.width);
	}
	

	p.y = distance+40;
	

	if( score<=500 ) //NORMAL PLATFORMS IN EVERY LINE
	{
		p.display = true;

		p.type = "normal";

		 


	}
	else if( score>500 && score<=1000) // NORMAL AND FAKE PLATFORMS IN EVERY LINE
	{
		type = rand()%15 + 1;

		p.display = true;

		if( type%2 != 0 || type%5!=0 )
			p.type = "normal";
		 

		else 
			{
				p.type = "fake";

				 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;
				p.type="normal";
			}
				
		 


				p.state = 1;
			}
	
		
	}

	else if( score>1000 && score<=2000 ) // NORMAL AND FAKE PLATFORMS AND EMPTY SPACE-------> SOME NORMAL PLATFORMS HAVE SPRINGS
	{
		type = rand()%15 + 1;

		if( type%3==0 || type%5==0 ) // NORMAL 
			{
				p.display = true;

				p.type = "normal";
		 


				if( spr.display==false ) // GENERATES THE SPRING
				{
					// cout<<" a spring is generated "<<endl;

					spr.display = true;

					spr.state = "rest";

					spr.x = rand()%(p.width - spr.width) + p.x;

					spr.y = p.y - spr.height;

					spr.Vx = 0;
				}
				



			}
		else if( type%7==0 ) //  EMPTY SPACE
			{
				p.display = false;

				p.type = "empty space";

				// cout << "ONE" << endl;

		 


				 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;
				p.type="normal";
			}

			}
		else if( type%2==1 )// 2/10 FAKE 
		{
			p.display = true;

			p.type = "fake";

			 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;

				p.type="normal";
			}
		 


			p.state = 1;


		}

		
		
	}
	else if( score>2000 && score<=5000 ) // NORMAL AND FAKE AND MOVING SIDE TO SIDE PLATFORMS IN EVERY LINE----> SOME PLATFORMS HAVE SPRING OR TRAMPOLIN
	{

		type = rand()%15 + 1;

		p.display = true;
		
		if( type%5==0 || type%3==0 ) // 7/15 MOVING SIDE TO SIDE
		{
			p.type = "moving side to side";
		 


			p.Vx = Vx;

			if( spr.display==false ) // GENERATES THE SPRING
				{
					// cout<<" a spring is generated "<<endl;

					spr.display = true;

					spr.state = "rest";

					spr.x = rand()%(p.width - spr.width) + p.x;

					spr.y = p.y - spr.height;
					
					spr.Vx = Vx;

					spr.leftd = spr.x - p.x;

					spr.rightd = p.x + p.width - ( spr.x + spr.width );

				} 

		}
		else if( type%2==0 ) // 4/15 NORMAL
		{
			p.type = "normal";
		 


			type = rand()%2;

			if( type==0 )
			{
				if( spr.display==false ) // GENERATES THE SPRING
							{
								// cout<<" a spring is generated "<<endl;
			
								spr.display = true;
			
								spr.state = "rest";
			
								spr.x = rand()%(p.width - spr.width) + p.x;
			
								spr.y = p.y - spr.height;
			
								spr.Vx = 0;
			
			
							} 
			}
			
		else
			{
				if( trm.display==false ) // GENERATES THE TRAMPOLIN
				{
					// cout<<" a trampolin is generated "<<endl;
			
					trm.display = true;
			
					trm.state = "f1";
			
					trm.x = rand()%(p.width - trm.width) + p.x;
			
					trm.y = p.y - trm.height;
			
					trm.Vx = 0;
			
			
				}
			}


		}


		
		else // 4/15 FAKE
		{
			p.type = "fake";
		 

 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;

				p.type="normal";
			}
			p.state = 1;
		}

		
	}

	else if( score>5000 && score<=10000 ) // NORMAL AND MOVING SIDE TO SIDE PLATFORMS AND EMPTY SPACE -----> SOME PLATFORMS HAVE SPRINGS
	{

		type = rand()%10 + 1;

		 if( type%4==0 || type%5==0 ) // 5/10 MOVING SIDE TO SIDE
		 {
		 	p.display = true;

		 	p.type = "moving side to side";
		 


		 	p.Vx = Vx;

		 	if( trm.display==false ) // GENERATES THE TRAMPOLIN
			{
					// cout<<" a trampolin is generated "<<endl;

					trm.display = true;

					trm.state = "f1";

					trm.x = rand()%(p.width - trm.width) + p.x;

					trm.y = p.y - trm.height;

					trm.Vx = Vx;

					trm.leftd = trm.x - p.x;

					trm.rightd = p.x + p.width - ( trm.x + trm.width );

			}

		 }
		 else if( type%3==0 ) // 3/10 EMPTY SPACE
		 {
		 	p.display = false;

		 	p.type = "empty space";

				// cout << "TWO" << endl;


		 	 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;

				p.type="normal";
			}
		 

		 }
		
		 else if(type%7==0){

		 }


		 else // 2/10 NORMAL
		 {
		 	p.display = true;

		 	p.type = "normal";

		 


		 		if( spr.display==false ) // GENERATES THE SPRING
				{
					// cout<<" a spring is generated "<<endl;

					spr.display = true;

					spr.state = "rest";

					spr.x = rand()%(p.width - spr.width) + p.x;

					spr.y = p.y - spr.height;

					spr.Vx = 0;

			} 
		 }

		
	}

	else if( score>10000 && score<=15000 ) // DISAPPEARING AND EMPTY SPACE ------> BLACK HOLE
	{
		type = rand()%7+1;

		if( type%2==0 || type%3==0 ) //  DISAPPEARING
		{
			p.display = true;

			p.type = "disappearing";
		 


			p.state = 1;

			count = count +1;

			cout<<"count is "<<count<<endl;

			if( count == 2 && blh.display==false )
			{
				blh.display = true;

				blh.x = rand()%50;

				blh.y = -( 6*p.height );
			}

			while( p.x<=150 ) // TO MAKE SURE THE BLACK HOLE DOESN'T OVERLAP WITH PLATFORMS
			{
				p.x = rand()%(SCREEN_WIDTH - (p.width + 150 )) + 150 ;
			}




		}
		else //  EMPTY SPACE
		{
			p.display = false;

			p.type = "empty space";

				// cout << "THREE" << endl;


		 	 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;

				p.type="normal";
			}

		 

		}

		
	}
	else if( score>15000 && score<=20000 )// DISAPPEARING AND MOVIND SIDE TO SIDE AND EMPTY SPACE
	{
		type = rand()%15 + 1;

		
		if( type%5==0 || type%3==0 ) // 7/15 MOVING SIDE TO SIDE
		{
			p.display = true;

			p.type = "moving side to side";
		 

		}
		else if( type%2==0 ) // 4/15 DISAPPEARING
		{
			p.display = true;

			p.type = "disappearing";
		 


			p.state = 1;

		}
		
		else // 4/15 EMPTY SPACE
		{
			p.display = false;

			p.type = "empty space";

				// cout << "FOUR" << endl;


		 	 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;

				p.type="normal";
			}

		 


		}

	}

	else if( score>20000 && score<=30000 ) // EXPLOSIVE AND NORMAL AND EMPTY SPACE
	{
		type = rand()%7+1;

		if( type%2==0 || type%3==0 ) //  EXPLOSIVE
		{
			p.display = true;

			p.type = "explosive";
		 


			p.state = 1;

		}
		else //  EMPTY SPACE
		{
			p.display = false;

			p.type = "empty space";

				// cout << "FIVE" << endl;


		 	 space_counter++;

			if (space_counter>2){
				 space_counter=0;
				 p.display = true;

				p.type="normal";
			}


		}
	}

/*	if (p.type=="moving side to side" && pa.type!="moving side to side"){
			if(p.x>pa.x + w){
				if (p.Vx<0)
					p.Vx*=(-1);
			}

			if(p.x+w<pa.x){
				if (p.Vx>0)
					p.Vx*=(-1);
			}

		} */

	 // cout<<"type is "<<p.type<<endl;
	 // cout<<space_counter<<endl;


}

void collision_detection( platform p[12] ,Dot &d , spring &spr , trampolin &trm , blackhole &blh , bool &play )
{
	int temp;
	temp = d.y+d.height;

	// SPRING COLLISION
	if( spr.display==true )
	{
		//cout << "we are [fucking] here " << endl;
		if( (d.y+d.height>=spr.y && d.y+d.height<spr.y+spr.height )  && 
				( ( spr.x>=d.x  &&  spr.x<=d.x+d.width ) || ( spr.x+spr.width>=d.x  &&  spr.x+spr.width<=d.x+d.width ) ) )
		{
			// HANDLE SPRING COLLISION
			Mix_PlayChannel( -1, springs, 0 );

			d.yVel = 30;

			spr.y = spr.y - 28;

			d.y = spr.y - d.height;

			spr.state = "stretched";

			// cout<< "spring collision"<<endl;
		}
	} 

	// TRAMPOLIN COLLISION
	if( trm.display==true )
	{
		if( (d.y+d.height>=trm.y && d.y+d.height<trm.y+trm.height )  && 
				( ( d.x>=trm.x  &&  d.x<=trm.x+trm.width ) || ( d.x+d.width>=trm.x  &&  d.x+d.width<=trm.x+trm.width ) ) )
		{
			// HANDLE TRAMPOLIN COLLISION

			Mix_PlayChannel( -1, tramp, 0 );


			d.yVel = 35;

			d.y = trm.y - d.height;

			trm.state = "f2";
		}
	} 

	// BLACK HOLE COLLISION
	if( blh.display==true )
	{
		if( d.x<=blh.x + blh.width )
		{
			play = false;
		}
	}

	// PLATFORMS COLLISION
	for( int i=0 ; i<n ; i++ )
	{
		if(  p[i].display==true && p[i].y>= 250 )
		{
			if( ( d.y+d.height>=p[i].y && d.y+d.height<p[i].y+p[i].height )  && 
				( ( d.x>p[i].x  &&  d.x<p[i].x+p[i].width ) || ( d.x+d.width>p[i].x  &&  d.x+d.width<p[i].x+p[i].width ) ) )
			{
				//collision has occured

				if( p[i].type == "normal" || p[i].type =="moving side to side" )
				{
			Mix_PlayChannel( -1, platforms, 0 );
					

					d.yVel = 25;

					d.y = p[i].y - d.height;

				}
				else if ( p[i].type == "fake" )
				{
			Mix_PlayChannel( -1, breaks, 0 );
					

					p[i].state = 2;

					p[i].y+=10;
				}
				else if( p[i].type=="disappearing" )
				{
			Mix_PlayChannel( -1, platforms, 0 );
					
					d.yVel = 25;

					d.y = p[i].y - d.height;

					if( p[i].state==1 )
					{
						p[i].state = 2;
					}
				}
				else if( p[i].type == "explosive" )
				{
			Mix_PlayChannel( -1, platforms, 0 );
					
					d.yVel = 25;

					d.y = p[i].y - d.height;

					if( p[i].state == 1 ) // if it's yellow change it to red
					{
			Mix_PlayChannel( -1, platforms, 0 );
						
						p[i].state = 2;
					}
					else if( p[i].state == 2 ) // if it's red make it exploded
					{
			Mix_PlayChannel( -1, explo, 0 );
						
						p[i].state = 3;
					}

				}
			}
		}

	}

} 


void displacement( platform p[12] , Dot &d , spring &spr , trampolin &trm, blackhole &blh , int &score , int &count , bool &play ) 
{
		

		// MOVE OBJECTS SIDE TO SIDE

		if( spr.Vx!=0 )
		{
			spr.x+=spr.Vx;

			if( (spr.x + spr.width + spr.rightd)>=SCREEN_WIDTH || spr.x<=spr.leftd )
			{
				spr.Vx = -spr.Vx;
			}
		}

		if( trm.Vx!=0 )
		{
			trm.x+=trm.Vx;

			if( (trm.x + trm.width + trm.rightd)>=SCREEN_WIDTH || trm.x<=trm.leftd )
			{
				trm.Vx = -trm.Vx;
			}
		}
		
		// MOVE PLATFORMS SIDE TO SIDE
		for( int i=0 ; i<n ; i++)
		{

			if( p[i].type == "moving side to side" )
			{
				p[i].x+=p[i].Vx;

				if( p[i].x + p[i].width>=SCREEN_WIDTH || p[i].x<=0 )
				{
					p[i].Vx = -p[i].Vx;
				}
				
			}

		}


	if( d.y <= 250 && d.yVel>0 ) // WHEN THE DOODLER IS MOVING UPWARDS
	{
		d.y = 250;	

		score += d.yVel;

		// MOVE OBJECTS DOWNWARDS
		double Vy = d.yVel;

		if( spr.display ) // SPRING
			spr.y+= Vy;

		if( trm.display ) // TRAMPOLIN
			trm.y+= Vy;

		if( blh.display ) // BLACK HOLE
			blh.y+= Vy;


		// CHECKS FOR EXCEEDING THE SCREEN

		if( spr.y>SCREEN_HEIGHT ) // SPRING
		{
			spr.display = false;
		}

		if( trm.y>SCREEN_HEIGHT ) // TRAMPOLIN
		{
			trm.display = false;
		}
		if( blh.y>SCREEN_HEIGHT )
		{
			blh.display = false;

			count = 0;
		}


		// MOVES PLATFORMS DOWNWARDS
		for( int i=0 ; i<n ; i++)
		{	
			//cout<<i<<" [before] platform's y is "<<p[i].y<<endl;

			p[i].y+= Vy;

			/*if( i==8 && abs( p[i].y-p[i-1].y )==30 )
			{
				p[i].y = p[i].y - 30;
			}*/

			//cout<<i<<" [after] platform's y is "<<p[i].y<<endl;

			// cout << "Vy = " << Vy << endl;
			// cout<<i<<" platform's y is "<<p[i].y << endl;
			// if(p[i].type!="empty space")
				// if(i<9)
					// if(p[i].y-(p[i-1].y+Vy)<30){
						// cout <<"ARRRRRRRRRRRRRRRRRRRR on "<< i <<endl;
						// p[i+1].y+=10;
						// cout << "New: " << p[i].y-p[i+1].y << endl;
					// }
				// if(i==9)
					// if(p[9].y-p[0].y+Vy<30)
						// cout <<"ARRRRRRRRRRRRRRRRRRRR on "<< 10 <<endl;


			
			// CHECKS FOR EXCEEDING THE SCREEN
			if( p[i].y>=SCREEN_HEIGHT)
			{
				//cout<<" platform "<<i<<" with y "<<p[i].y<<" is going for generate "<<endl;

				double distance = p[i].y - SCREEN_HEIGHT; // SOLOUTION
				//cout <<"distance = "<<distance <<endl;
							
				p[i].display = false;
				int a; if(i<n-1) a=i+1; else if(i==n-1) a=0;
				int b; if(i>0) b=i-1; else if(i==0) b=n-1;

				generate( p[i] , p[a], p[b], spr, trm , blh , score , count , distance, Vy );		// GENERATE FUNCTION IS CALLED

			}
		}

	}

	else if( d.yVel<0 ) // WHEN THE DOODLER IS MOVING DOWNWARDS
	{
		collision_detection( p , d ,spr , trm , blh , play );

	}

			
} 



void first_generation( platform p[12] , Dot &d , spring &spr , trampolin &trm , blackhole &blh )
{
	// DOODLER DIMENTION
	d.width = 60;
	d.height = 60;
    
    d.x = (SCREEN_WIDTH - d.width)/2;
    d.y = SCREEN_HEIGHT - d.height;
    //Initialize the velocity
    d.xVel = 0;
    d.yVel = 25;

	// SPRING DIMENTION
	spr.height = 23;
	spr.width = 34;
	spr.display = false;


	// TRAMPOLIN DIMENTION
	trm.height = 27;
	trm.width = 71;
	trm.display = false;
/*
	// JETPACK DIMENTION
	jpc.weight = 26;
	jpc.height = 83;
	jpc.display = false;
	jpc.state = 2; */

	// BLACK HOLE DIMENTION
	blh.height = 144;
	blh.width = 148;
	blh.display = false;

	// PLATFORMS DIMENTION
	for( int i=0; i<10; i++ )
	{
		p[i].height = 30;

		p[i].width = 114;

		p[i].display = true;

		p[i].type = "normal";

		p[i].x = rand()%(SCREEN_WIDTH - p[i].width);

		p[i].y = SCREEN_HEIGHT - ((i*2+1)*p[i].height);
		// p[i].y = SCREEN_HEIGHT - (i)*75;
	}

}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    } 

    //Set the window caption
    SDL_WM_SetCaption( "DOODLE JUMP", NULL );

    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( dot );
    SDL_FreeSurface( dotu );
    SDL_FreeSurface( dotl );
    SDL_FreeSurface( dotr );
    SDL_FreeSurface( normal_platform );
    SDL_FreeSurface( fake_platform_1 );
    SDL_FreeSurface( fake_platform_2 );
    SDL_FreeSurface( fake_platform_3 );
    SDL_FreeSurface( fake_platform_4 );
    SDL_FreeSurface( moving_side_to_side_platform );
    SDL_FreeSurface( disappearing_platform_1 );
    SDL_FreeSurface( disappearing_platform_2 );
    SDL_FreeSurface( explosive_red_platform );
    SDL_FreeSurface( explosive_yellow_platform );
    SDL_FreeSurface( exploded_platform );
    SDL_FreeSurface( spring_rest );
    SDL_FreeSurface( spring_stretched );
    SDL_FreeSurface( trampolin_f1 );
    SDL_FreeSurface( trampolin_f2 );
    SDL_FreeSurface( trampolin_f3 );
    SDL_FreeSurface( black_hole );
    SDL_FreeSurface( Score );
    SDL_FreeSurface( HiScore );
    SDL_FreeSurface( resume_button );
    SDL_FreeSurface( play_button );
    SDL_FreeSurface( menu_back );
    SDL_FreeSurface( menu_button );
    SDL_FreeSurface( pause_button );
    SDL_FreeSurface( game_over );
    SDL_FreeSurface( playagain );

    Mix_FreeChunk( tramp );
    Mix_FreeChunk( springs );
    Mix_FreeChunk( over );
    Mix_FreeChunk( platforms );
    Mix_FreeChunk( breaks );
    Mix_FreeChunk( explo );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void load_stuff( )
{
	tramp = Mix_LoadWAV( "trampoline.wav" );
    springs = Mix_LoadWAV( "feder.wav" );
    over = Mix_LoadWAV( "pada.wav" );
    explo = Mix_LoadWAV( "explode.wav" );
    platforms = Mix_LoadWAV( "bijeli.wav" ); 
    breaks = Mix_LoadWAV( "lomise.wav" );	

	play_button = load_image( "play.png" );
    SDL_SetColorKey (play_button, SDL_SRCCOLORKEY, SDL_MapRGB ( play_button -> format, 255, 0, 0));


    menu_back = load_image( "menu.png" );
    pause_back = load_image( "pause_back.png" );

    resume_button = load_image( "resume.png" );
    SDL_SetColorKey (resume_button, SDL_SRCCOLORKEY, SDL_MapRGB ( resume_button -> format, 255, 0, 0));

    pause_button = load_image( "pause_button.png" );
    SDL_SetColorKey (pause_button, SDL_SRCCOLORKEY, SDL_MapRGB ( pause_button -> format, 255, 0, 0));

    menu_button = load_image( "menu_button.png" );
    SDL_SetColorKey (menu_button, SDL_SRCCOLORKEY, SDL_MapRGB ( menu_button -> format, 255, 0, 0));

    playagain = load_image( "playagain.png" );
    SDL_SetColorKey (playagain, SDL_SRCCOLORKEY, SDL_MapRGB ( playagain -> format, 255, 0, 0)); 

    game_over = load_image( "game_over.png" );


	background = load_image( "bck_M.png" );
	dot = load_image( "Doodler6060r.png" );

	dotr = load_image( "Doodler6060r.png" );
	dotl = load_image( "Doodler6060l.png" );
	dotu = load_image( "Doodler6060u.png" );

	SDL_SetColorKey (dot, SDL_SRCCOLORKEY, SDL_MapRGB ( dot -> format, 255, 0, 228));
	SDL_SetColorKey (dotr, SDL_SRCCOLORKEY, SDL_MapRGB ( dot -> format, 255, 0, 228));
	SDL_SetColorKey (dotl, SDL_SRCCOLORKEY, SDL_MapRGB ( dot -> format, 255, 0, 228));
	SDL_SetColorKey (dotu, SDL_SRCCOLORKEY, SDL_MapRGB ( dot -> format, 255, 0, 228));


    normal_platform = load_image("normal_platform.png");
    SDL_SetColorKey (normal_platform, SDL_SRCCOLORKEY, SDL_MapRGB ( normal_platform -> format, 255, 0, 228));

    fake_platform_1 = load_image( "fake_platform_1.png" );
    SDL_SetColorKey (fake_platform_1, SDL_SRCCOLORKEY, SDL_MapRGB ( fake_platform_1 -> format, 255, 0, 228));


    fake_platform_2 = load_image( "fake_platform_2.png" );
    SDL_SetColorKey (fake_platform_2, SDL_SRCCOLORKEY, SDL_MapRGB ( fake_platform_2 -> format, 255, 0, 228));

    fake_platform_3 = load_image( "fake_platform_3.png" );
    SDL_SetColorKey (fake_platform_3, SDL_SRCCOLORKEY, SDL_MapRGB ( fake_platform_3 -> format, 255, 0, 228));

    fake_platform_4 = load_image( "fake_platform_4.png" );
    SDL_SetColorKey (fake_platform_4, SDL_SRCCOLORKEY, SDL_MapRGB ( fake_platform_4 -> format, 255, 0, 228));

    moving_side_to_side_platform = load_image( "moving_side_to_side.png" );
    SDL_SetColorKey (moving_side_to_side_platform, SDL_SRCCOLORKEY, SDL_MapRGB ( moving_side_to_side_platform -> format, 255, 0, 228));

    disappearing_platform_1 = load_image( "disappearing_1.png" );
    SDL_SetColorKey (disappearing_platform_1, SDL_SRCCOLORKEY, SDL_MapRGB ( disappearing_platform_1 -> format, 255, 0, 228));

    disappearing_platform_2 = load_image( "disappearing_2.png" );
    SDL_SetColorKey (disappearing_platform_2, SDL_SRCCOLORKEY, SDL_MapRGB (disappearing_platform_2 -> format, 255, 0, 228));

    explosive_yellow_platform = load_image( "explosive_yellow.png" );
    SDL_SetColorKey (explosive_yellow_platform , SDL_SRCCOLORKEY, SDL_MapRGB ( explosive_yellow_platform  -> format, 255, 0, 228));

    explosive_red_platform = load_image( "explosive_red.png" );
    SDL_SetColorKey (explosive_red_platform, SDL_SRCCOLORKEY, SDL_MapRGB ( explosive_red_platform-> format, 255, 0, 228));

    exploded_platform = load_image( "exploded.png" );
    SDL_SetColorKey (exploded_platform, SDL_SRCCOLORKEY, SDL_MapRGB ( exploded_platform -> format, 255, 0, 228));

    spring_rest = load_image( "baste.png" );
    SDL_SetColorKey (spring_rest, SDL_SRCCOLORKEY, SDL_MapRGB ( spring_rest -> format, 255, 0, 228));

    spring_stretched = load_image( "baz.png" );
    SDL_SetColorKey (spring_stretched, SDL_SRCCOLORKEY, SDL_MapRGB ( spring_stretched -> format, 255, 0, 0));

    trampolin_f1 = load_image( "trampolinf1.png" );
    SDL_SetColorKey (trampolin_f1, SDL_SRCCOLORKEY, SDL_MapRGB ( trampolin_f1 -> format, 255, 0, 228));

    trampolin_f2 = load_image( "trampolinf2.png" );
    SDL_SetColorKey (trampolin_f2, SDL_SRCCOLORKEY, SDL_MapRGB ( trampolin_f2 -> format, 255, 0, 228));

    trampolin_f3 = load_image( "trampolinf3.png" );
    SDL_SetColorKey (trampolin_f3, SDL_SRCCOLORKEY, SDL_MapRGB ( trampolin_f3-> format, 255, 0, 228));

    //jetpack = load_image( "" );

    black_hole = load_image( "hole_X.png" );
    SDL_SetColorKey (black_hole, SDL_SRCCOLORKEY, SDL_MapRGB ( black_hole -> format, 255, 0, 228));

    
    //Open the font
    font = TTF_OpenFont( "DoodleJump.ttf", 30 );

}

int highscore_control(int score){
	int f;
	int highscore;
    ifstream inFile;
    
    
    inFile.open("hs.txt");
    inFile >> f;
    
	if (score>f){

    	highscore = score;
    	std::ofstream ofs;
		ofs.open("hs.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		
		
		std::ofstream ofss;
		ofss.open("hs.txt");
		ofss << score;
		ofss.close();
	}

	else {
		highscore = f;
	}
	//cout<<"highscore is "<<highscore<<endl;
	return highscore;
}

void display_stuff( platform p[12] , Dot &d ,spring &spr , trampolin &trm , blackhole &blh , double &pause_x , double &pause_y , int &score )
{

	// DISPLAY PLATFORMS
	for( int i=0 ; i<n ; i++)	
	{
		if( p[i].display == true )
		{
			if( p[i].type == "fake"  )
			{
				if( p[i].state == 1 )
					{
						apply_surface( p[i].x, p[i].y, fake_platform_1, screen);

					}
				else if( p[i].state == 2 )
				{
					apply_surface( p[i].x, p[i].y, fake_platform_2, screen);

					p[i].y+=10;

					p[i].state = 3;

				}
				else if( p[i].state == 3 )
				{
					apply_surface( p[i].x, p[i].y, fake_platform_3, screen);

					p[i].y+=10;

					p[i].state = 4;
				}
				else if( p[i].state == 4 )
				{
					apply_surface( p[i].x, p[i].y, fake_platform_4, screen);

					p[i].display = false;

					p[i].type = "empty space";
				}
			}
			else if( p[i].type == "normal" )
			{
				apply_surface( p[i].x, p[i].y, normal_platform, screen);
				//cout<<"normal is shown"<<endl;
			}
			else if( p[i].type == "moving side to side" )
			{
				apply_surface( p[i].x, p[i].y,  moving_side_to_side_platform, screen);
				//cout<<"moving side to side is shown"<<endl;
			}
			else if( p[i].type == "disappearing" )
			{
				if( p[i].state == 1 )
				{
					apply_surface( p[i].x, p[i].y, disappearing_platform_1, screen );
				}
				else if( p[i].state == 2 )
				{
					apply_surface( p[i].x, p[i].y, disappearing_platform_2, screen );

					p[i].display = false;

					p[i].type = "empty space";
				}
			}
			else if( p[i].type == "explosive" )
			{
				if( p[i].state == 1 ) // YELLOW
				{
					apply_surface( p[i].x , p[i].y , explosive_yellow_platform , screen );
				}
				else if( p[i].state == 2 ) // RED
				{
					apply_surface( p[i].x , p[i].y , explosive_red_platform , screen );
				}
				else if( p[i].state == 3 ) // EXPLODED
				{
					apply_surface( p[i].x , p[i].y , exploded_platform , screen );

					p[i].display = false;

					p[i].type = "empty space";

				}
			}
		}

	}
	
	// DISPLAY OBJECTS

	if( spr.display == true ) // SPRING
	{
		
		if( spr.state=="rest" )
			{
				apply_surface( spr.x , spr.y , spring_rest, screen );
				//cout<<" spring x is "<<spr.x<<" spring y is "<<spr.y<<endl;
			}
		else if( spr.state == "stretched" )
			{
				apply_surface( spr.x , spr.y , spring_stretched , screen );
			}
	}


	if( trm.display == true ) // TRAMPOLIN
	{
		
		if( trm.state=="f1" )
			{
				apply_surface( trm.x , trm.y , trampolin_f1, screen );
				
			}
		else if( trm.state=="f2" )
		{
			apply_surface( trm.x , trm.y , trampolin_f2, screen );

			trm.state = "f3";

		}
		else if( trm.state=="f3" )
		{
			apply_surface( trm.x, trm.y, trampolin_f3, screen );
		}
	}

	if( blh.display==true ) // BLACK HOLE
	{
		apply_surface( blh.x , blh.y , black_hole , screen );
	}


	// DISPLAY THE DOODLER
	apply_surface( d.x, d.y, dot, screen );

	// DISPLAY THE SCORE
	
	stringstream ss;
	ss << score;
	string str = ss.str();
	string score_text = "Score: " + str;
	Score = TTF_RenderText_Solid( font, score_text.c_str() , textColor);
	apply_surface( 5 , 5 , Score , screen );

	int highscore = highscore_control(score);
	stringstream sos;
	sos << highscore;
	string hstr = sos.str();
	string highscore_text = "HScore: " + hstr;
	HiScore = TTF_RenderText_Solid( font, highscore_text.c_str() , textColor);
	apply_surface( 200 , 5 , HiScore , screen );

	//DISPLAY THE PAUSE BUTTON
	apply_surface( pause_x , pause_y , pause_button , screen );
}

int main_game( bool &play, bool &pause , bool &gameover, platform p[12] , Dot &d , spring &spr , trampolin &trm, blackhole &blh  , Timer &fps )
{

	int count = 0; // USED FOR GENERATING BLACK HOLE

    first_generation( p , d ,spr , trm  , blh );

    // SET SCORE
    int score = 0;

    // PAUSE BUTTON DIMENTION
    double pause_x = 150;
    double pause_y = 2.5;
    int pause_h = 35;
    int pause_w = 35;

    while( play && score<=30000 )
    {	
    	//Start the frame timer
        fps.start();

    	apply_surface( 0, 0, background, screen);

    	display_stuff( p, d , spr , trm , blh , pause_x , pause_y , score );

    	d.handle_input(play , pause , pause_x , pause_y , pause_h , pause_w );

    	d.move(play , gameover);

    	displacement( p , d , spr , trm , blh , score , count , play );
    	 
    	highscore_control( score );

    	if( SDL_Flip( screen ) == -1 )
    	{
        	play = false;
        	break;
    	}

    	

    //If there was an error in rendering the text 

    //Apply the images to the screen
    

    	//SDL_FreeSurface( screen );

    	SDL_Delay( 100 );

    	//Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
	}

	return score;
}

void start_menu( bool &play )
{

	// PLAY BUTTON DIMENTION
	int p_h = 62;
	int p_w = 170;
	int p_x = 30;
	int p_y = 350;

	//The mouse offsets
    int x = 0, y = 0;

    bool foo = true;

    while ( foo )
    {
    	// DISPLAY BACKGROUND
		apply_surface( 0, 0, menu_back, screen);

		// DISPLAY PLAY BUTTON
		apply_surface( p_x, p_y, play_button , screen);

		while ( SDL_PollEvent( &event ) )
		{
		
			if( event.type == SDL_MOUSEBUTTONDOWN )
    		{
        		//If the left mouse button was pressed
        		if( event.button.button == SDL_BUTTON_LEFT )
        		{
            		//Get the mouse offsets
            		x = event.button.x;
            		y = event.button.y;
        
            		if( (x>p_x) && (x<p_x + p_w) && (y>p_y) && (y<p_y + p_h) )
            		{
        						play = true;

	        					foo = false;

        			}

            	}
            }
        	//If the user has Xed out the window
        	else if( event.type == SDL_QUIT )
        	{
            	//Quit the program
            	play = false;
            	foo = false;
        	}

        

        	if( SDL_Flip( screen ) == -1 )
			{
				play = false;
				foo = false;
			}

		}
    }

}

void game_over_menu( bool &play, bool &gameover , int score )
{
	
	Mix_PlayChannel( -1, over, 0 );


	// PLAY AGAIN BUTTON DIMENTION
	int pa_x = 120;
	int pa_y = 380;
	int pa_h = 62;
	int pa_w = 170;

	// MENU BUTTON DIMENTION
	int m_x = 120;
	int m_y = 460;
	int m_h = 62;
	int m_w = 170;

	//The mouse offsets
    int x = 0, y = 0;

	while( gameover )
	{
		// DISPLAY BACKGROUND
		apply_surface( 0, 0, game_over, screen);

		// DISPLAY PLAY AGAIN BUTTON
		apply_surface( pa_x, pa_y, playagain , screen);

		// DISPLAY MENU BUTTON
		apply_surface( m_x , m_y , menu_button , screen );

		stringstream ss;
	ss << score;
	string str = ss.str();
	string score_text = str;
	Score = TTF_RenderText_Solid( font, score_text.c_str() , textColor);
	apply_surface( 255 , 260 , Score , screen );

	int highscore = highscore_control(score);
	stringstream sos;
	sos << highscore;
	string hstr = sos.str();
	string highscore_text = hstr;
	HiScore = TTF_RenderText_Solid( font, highscore_text.c_str() , textColor);
	apply_surface( 240 , 305, HiScore , screen );

		while ( SDL_PollEvent( &event ) )
		{
		
			if( event.type == SDL_MOUSEBUTTONDOWN )
    		{
        		//If the left mouse button was pressed
        		if( event.button.button == SDL_BUTTON_LEFT )
        		{
            		//Get the mouse offsets
            		x = event.button.x;
            		y = event.button.y;
        
        			// HITTING PLAY AGAIN BUTTON
            		if( (x>pa_x) && (x<pa_x + pa_w) && (y>pa_y) && (y<pa_y + pa_h) )
            		{
        						play = true;

        						gameover = false;

        			}
        			// HITTING MENU BUTTON
        			else if( (x>m_x) && (x<m_x + m_w) && (y>m_y) && (y<m_y + m_h) )
            		{
        						play = true;

        						gameover = false;

        						start_menu( play );

        			}

            	}
            }

        	//If the user has Xed out the window
        	else if( event.type == SDL_QUIT )
        	{
            	//Quit the program
            	gameover = false;

        	}

        

        	if( SDL_Flip( screen ) == -1 )
			{
				play = false;
			}

		}
    }

	
}

int main( int argc, char* args[] )
{
   srand(time(NULL));

    //Initialize
    if( init() == false )
    {
        return 1;
    }

     //The frame rate regulator
    Timer fps;

    //The doodler that will be used
    Dot d;

    // CREATS PLATFORMS
    platform p[n];

    // CREATS SPRING
    spring spr;

    // CREATS TRAMPOLIN
    trampolin trm;

    // CREATS JETPACK;
    //jetpack jpc;

    // CREATS BLACK HOLE
    blackhole blh;

    // LOADS ALL IMAGES
    load_stuff( );

    // 
    bool play = false;
    bool pause = false;
    bool gameover = false;

    start_menu( play );

    while( play )
    {	
    
        int score = main_game( play, pause , gameover , p , d , spr , trm , blh , fps );

        game_over_menu( play, gameover , score );
    }

    clean_up();

    return 0;
}