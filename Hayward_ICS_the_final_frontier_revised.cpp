
//hayward space alien dude ICS3U game

#include <stdlib.h>
#include <stdio.h>
#include <allegro.h> 
#include <winalleg.h>
#include <time.h>

volatile long speed_counter = 0; 
volatile int ticks=0;
volatile int seconds=0;
volatile double elapsed_time = 0;

// structure used to control the many aspects of the array of invaders and bullets 
struct bull{
       
       int active;           //wether the item is active or not
       int xpos;             //the variable used to change the x position of the item
       int ypos;             //the variable used to change the y position of the item
       int bb_left;          //the value representing the left side of the bounding box of the item
       int bb_right;         //the value representing the right side of the bounding box of the item
       int bb_top;           //the value representing the top side of the bounding box of the item
       int bb_bottom;        //the value representing the bottom side of the bounding box of the item
};

bull bullet[100];            //array of bullets
bull invada[100];            //array of invaders

void do_elapsed_time() {     
     elapsed_time += 1; 
     }
END_OF_FUNCTION(do_elapsed_time);
								 
void increment_speed_counter(){  //function to keep track of the number of times the program runs though to keep the game clock running
	speed_counter++; 
}
END_OF_FUNCTION(increment_speed_counter); 

void ticker()
   {
      ticks++;
   }
END_OF_FUNCTION(ticker);

void seconds_count()
   {
      seconds++;
   }
END_OF_FUNCTION(seconds);

int background_y_position = -600;         //declaring and initializing the first of two background 
int background1_y_position = -1200;       //declaring and initializing the second background

BITMAP *buffer;            //declare the bitmaps that will be used
BITMAP *plane ;
BITMAP *invader ;

BITMAP *gameover ;
BITMAP *background;
BITMAP *background1;
BITMAP *bulletbit;

void bullet_fly(){         //the function responsible for making the bullets move
     int x;
     for(x=0;x<100;x++){
                 if(bullet[x].active == TRUE){        //the bullet is only moved if it is active
                         
                         bullet[x].ypos -= 7;         //move the bullet up by 7 units
                 }
            }
}

void invader_fly(){      //the function responsible for making the invaders and the background move down the screen
     int x;
     for(x=0;x<10;x++){
         if(invada[x].active == TRUE){
                 //allegro_message("wow man");
                 invada[x].ypos +=rand() % 7 +1;
         }
    }


     
     background_y_position++;            //make the two background images move down the screen
     background1_y_position++;
       
}
END_OF_FUNCTION(invader_fly);

//the function responsible for the collision detection between the plane and the invaders 
int collision_detect(int plane_bb_left, int plane_bb_top, int plane_bb_right, int plane_bb_bottom, struct bull *invada){
        
        int z=8;
        int collision = FALSE;          //start the collision as being no true
      
        
        for(z=0;z<10;z++){              //loop through all 10 invaders
                
                if(plane_bb_bottom < invada[z].bb_top)     //check the 4 sides for any overlap
                {
                				
                    collision= FALSE;
    			}
    			else if(plane_bb_top > invada[z].bb_bottom)
    			{
    				collision= FALSE;
    			}
    			else if(plane_bb_right < invada[z].bb_left)
    			{
    				collision= FALSE;
    			}
    			else if(plane_bb_left > invada[z].bb_right)
    			{
    				collision= FALSE;
    			}
    			else  {
                      //if there is overlap then return a value of true from the colision 
                      //allegro_message("collision detection is working for invader %d,  %d", z, collision);
                      return TRUE;
                }
                
        }
        return(collision);
}
END_OF_FUNCTION(collision_detect);   

//colision detection between the bullet and the invaders 
int collision_detect_bullet(int plane_bb_left, int plane_bb_top, int plane_bb_right, int plane_bb_bottom, struct bull *bullet, struct bull *invada){
        
        int z, y;
        int collision = FALSE;                 //start off by making the colision not true
        
        for(z=0;z<10;z++){
                for(y=0;y<100;y++){
                        if(bullet[y].active == TRUE){      //only check the collision if the bullet is active 
                                
                                if(invada[z].bb_bottom < bullet[y].bb_top)
                                {
                                				
                                    collision= FALSE;
                    			}
                    			else if(invada[z].bb_top > bullet[y].bb_bottom)
                    			{
                    				collision= FALSE;
                    			}
                    			else if(invada[z].bb_right < bullet[y].bb_left)
                    			{
                    				collision= FALSE;
                    			}
                    			else if(invada[z].bb_left > bullet[y].bb_right)
                    			{
                    				collision= FALSE;
                    			}
                    			else  {
                                      invada[z].ypos = -100;                   //if the collision is true reset the invader to -100 
                                      invada[z].xpos=rand() % 600 +1;          //reset the invaders x position to a random position along the x axis
                                      bullet[y].active = FALSE;                //make the bullet inactive 
                                      return TRUE;                             //return a collision value of true
                                }
                        }
                }          
        }
        return(collision);
}
END_OF_FUNCTION(collision_detect);

int main(int argc, char *argv[])
{
	srand(time(NULL));
    allegro_init(); 
	install_keyboard(); 
	install_timer(); 

    int x;
 
    for(x=0;x<6;x++){           //initialize the
         invada[x].ypos = -100;
         
    }
    
    for(x=6;x<10;x++){
             invada[x].ypos = -300;
             
    }
    

    int gameover_x_position = 200; 
    int gameover_y_position = 200;
    
    
    
    for(x=0;x<10;x++){
         invada[x].xpos =200;
    }
    
    int plane_x_position = 250; 
	int plane_y_position = 200;
	
	background_y_position = 0;
	background1_y_position = 0;
	//int invader_y_position = 200;
	
	int plane_bb_left = 0;
    int plane_bb_top = 0;
	int plane_bb_right = 0;
    int plane_bb_bottom = 0;
    
    for(x=0;x<10;x++){
         invada[x].bb_left =0;
         invada[x].bb_right =0;
         invada[x].bb_top =0;
         invada[x].bb_bottom =0;
    }
    
    for(x=0;x<100;x++){
         bullet[x].bb_left =0;
         bullet[x].bb_right =0;
         bullet[x].bb_top =0;
         bullet[x].bb_bottom =0;
    }
    
    int show_bbox = FALSE;
	
	int collision = FALSE;
    int bullet_count =0;
	int lose;
	int firsttime = 0;
	
	LOCK_VARIABLE(invader_y_position); 
	LOCK_FUNCTION(invader_fly);
	
	LOCK_VARIABLE(speed_counter); 
	LOCK_FUNCTION(increment_speed_counter);
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));
	
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    
    install_int(ticker,10);
    install_int_ex(ticker, BPS_TO_TIMER(100));
    
    LOCK_VARIABLE(seconds);
    LOCK_FUNCTION(seconds_count);
  
    install_int(seconds_count,10);
    install_int_ex(seconds_count, SECS_TO_TIMER(100));
    
    LOCK_VARIABLE(elapsed_time);
    LOCK_FUNCTION(do_elapsed_time);
    install_int_ex(do_elapsed_time, BPS_TO_TIMER(1)); 
    		
	set_color_depth(desktop_color_depth()); 
			
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); 
	
	BITMAP *buffer = create_bitmap(640,480); 
	
	char direction[10];
	
	if(buffer == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("Error: Could not create buffer!");
	    exit(EXIT_FAILURE);
	}
				
	
	BITMAP *plane = load_bitmap("plane.bmp", NULL);
	if(plane == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0); 
		allegro_message("Error: Could not load plane.bmp");
		exit(EXIT_FAILURE);
	}
	
	BITMAP *invader = load_bitmap("invader.bmp", NULL); 
	if(invader == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0); //Set the screen mode for allegro messages
		allegro_message("Error: Could not load invader.bmp");
		exit(EXIT_FAILURE);
	}
    
    BITMAP *gameover = load_bitmap("gameover.bmp", NULL);
	if(gameover == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0); 
		allegro_message("Error: Could not load gameover.bmp");
		exit(EXIT_FAILURE);
	}
    
    BITMAP *background = load_bitmap("stars.bmp", NULL);
	if(background == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0); 
		allegro_message("Error: Could not load stars.bmp");
		exit(EXIT_FAILURE);
	}
	
	BITMAP *background1 = load_bitmap("stars.bmp", NULL);
	if(background1 == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0); 
		allegro_message("Error: Could not load stars.bmp");
		exit(EXIT_FAILURE);
	}
    
    BITMAP *bulletbit = load_bitmap("bullet.bmp", NULL);
	if(bullet == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0); 
		allegro_message("Error: Could not load bullet.bmp");
		exit(EXIT_FAILURE);
	}
    
    BITMAP *intro = load_bitmap("intro.bmp", NULL);
	if(intro == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0); 
		allegro_message("Error: Could not load intro.bmp");
		exit(EXIT_FAILURE);
	}
    		
    gameover_x_position = 200; 
    gameover_y_position = 200;
   
    plane_x_position = 250; 
	plane_y_position = 320;
	
    for(x=0;x<10;x++){
         invada[x].xpos =rand() % 400 +1;
    }    
    
	int counttimes=0;
	int shoot_time =0;
	int collision_bullet;
	int bullet_num = 0;
	float bullet_accuracy= 0;
	int play = 0;
	int fresh =TRUE;
	
	for(x=0;x<10;x++)
                invada[x].active = TRUE;
	
	for(x=0;x<100;x++)
                bullet[x].active = FALSE;
    
    //while the player has not presed the escape key 
	while(!key[KEY_ESC]) 
	{
           draw_sprite(screen, intro, 0, 0);
           
           if(key[KEY_ENTER]){
                  play = 1;
                  clear(screen);
                  clear(buffer);
           }
           
           while(play == 1) 
    	   {            
                        if(fresh == TRUE){       
                        for(x=0;x<6;x++){           //initialize the
                        invada[x].ypos = -100;
                             
                        }
                        
                        for(x=6;x<10;x++){
                                 invada[x].ypos = -300;
                                 
                        }
                        
                    
                        int gameover_x_position = 200; 
                        int gameover_y_position = 200;
                        
                        
                        
                        for(x=0;x<10;x++){
                             invada[x].xpos =200;
                        }
                        
                        int plane_x_position = 250; 
                    	int plane_y_position = 200;
                    	
                    	background_y_position = 0;
                    	background1_y_position = 0;
                    	//int invader_y_position = 200;
                    	
                    	int plane_bb_left = 0;
                        int plane_bb_top = 0;
                    	int plane_bb_right = 0;
                        int plane_bb_bottom = 0;
                        
                        for(x=0;x<10;x++){
                             invada[x].bb_left =0;
                             invada[x].bb_right =0;
                             invada[x].bb_top =0;
                             invada[x].bb_bottom =0;
                        }
                        
                        for(x=0;x<100;x++){
                             bullet[x].bb_left =0;
                             bullet[x].bb_right =0;
                             bullet[x].bb_top =0;
                             bullet[x].bb_bottom =0;
                        }
                               
                        plane_x_position = 250; 
	                    plane_y_position = 320;    
                     }   
                               //allegro_message("times through = %d",counttimes++);
                               printf("\nplay = %d", play);
                		while(speed_counter > 0) // Do the logic loop while the speed counter is > 0.
                		{
                                       
                			
                			if(key[KEY_LEFT]){
                				if(plane_x_position>0)
                                     plane_x_position  -=5;
                				//direction= 'left';
                            }
                			
                			if(key[KEY_RIGHT]){
                				if(plane_x_position<608)
                                     plane_x_position +=5;
                				//direction= 'right';
                            }
                			
                			if(firsttime < 100)
                                     firsttime ++;
                            else
                                  invader_fly();
                                  
                            //textprintf_ex(buffer, font, 0,0, makecol(255,255,255),"%p : %p", ticks, seconds);
                                        
                            plane_bb_left = plane_x_position;
                            plane_bb_top = plane_y_position;
                        	plane_bb_right = (plane_bb_left + 32);
                            plane_bb_bottom = (plane_bb_top + 66);
                            
                            for(x=0;x<10;x++){          //initialize the bounding box of the array of the inavders
                                 invada[x].bb_left =invada[x].xpos;
                                 invada[x].bb_top =invada[x].ypos;
                                 invada[x].bb_right =(invada[x].bb_left + 53);
                                 invada[x].bb_bottom =(invada[x].bb_top + 53);
                            } 
                            
                            
                            
                            if(key[KEY_ALT])        //when the player presses the alt key, make show_bbox true
                				show_bbox = TRUE;
                			
                			else if(!key[KEY_ALT])       //if the player is not pressing the alt key dont make show_bbox true
                				show_bbox = FALSE;
                			
                			
                          	
                          	bullet_fly();
                          	
                          	for(x=0;x<100;x++){
                                 bullet[x].bb_left =bullet[x].xpos;
                                 bullet[x].bb_top =bullet[x].ypos;
                                 bullet[x].bb_right =(bullet[x].bb_left + 3);
                                 bullet[x].bb_bottom =(bullet[x].bb_top + 6);
                            }
                                
                          	for(x=0;x<100;x++){
                                 if(bullet[x].active == FALSE){
                                         bullet[x].xpos = (plane_x_position + 14);
                                         bullet[x].ypos = plane_y_position;
                                 }
                            }
                			
                            if(play == 1){
                                		collision = TRUE;	
                                    	collision= collision_detect(plane_bb_left, plane_bb_top, plane_bb_right, plane_bb_bottom, invada);
                                        //allegro_message("collision = %d", collision);
                                        //printf("\ncollision = %d", collision);
                                        if(collision == TRUE || collision == -1){
                                            //allegro_message("I have made it this far");
                                            
                                            clear(buffer);
                                            draw_sprite(buffer, gameover, gameover_x_position, gameover_y_position);
                                            allegro_message("GAME OVER");
                                            allegro_message("Kills: %d invaders \nAccuracy: %2f %%",bullet_num, ((bullet_num/bullet_accuracy)*100));
                                            //allegro_message("GAME OVER");
                                            exit(EXIT_FAILURE);
                                        }
                                        
                                        //collision_bullet= FALSE;
                                        collision_bullet= collision_detect_bullet(plane_bb_left, plane_bb_top, plane_bb_right, plane_bb_bottom, bullet, invada);
                                        //printf("\ncollision_bullet = %d", collision_bullet);
                                        if(collision_bullet == TRUE || collision_bullet == -1){
                                            bullet_num++;            
                                            
                                            textprintf_ex(buffer, font, 0,0, makecol(255,255,255), -1, "Collision!"); 
                                        }
                            }
                            speed_counter --; 
                            
                            if(key[KEY_ESC]){
                                            play = 0;
                                            clear_keybuf();
                                            allegro_message("wow");
                                            }
                            clear_keybuf(); 
                            fresh = FALSE;               
                        } 
                		
    		if(firsttime == 0){       //only move the figures after a 5 second pause
                         firsttime = 1;
                         Sleep(5000);
                         }
    		draw_sprite(buffer, background, 0, background_y_position);        //draw the background and the plane
    		draw_sprite(buffer, background1, 0, background1_y_position);
    		draw_sprite(buffer, plane, plane_x_position, plane_y_position); 
    		
            for(x=0;x<10;x++)       //draw the array of invaders 
                           draw_sprite(buffer, invader, invada[x].xpos, invada[x].ypos); 
    		
    		
    		for(x=0;x<100;x++){       //draw the array of bullets, but only draw the bullet if it is active 
                     if(bullet[x].active == TRUE){
                             draw_sprite(buffer, bulletbit, bullet[x].xpos, bullet[x].ypos);
                             
                     }
                }
    		
    		
    		//if the player presses the space bar 
    		if(key[KEY_SPACE]){
                    if(shoot_time%25== 0){
                            if(bullet_count == 100)         //if the bullet count reaches the limit of the array, start over
                                            bullet_count= 0;
                            
                            bullet[bullet_count].active = TRUE;     //make the bullet active
                            
                            bullet_accuracy++;
                            //draw the bullet to the buffer
                            draw_sprite(buffer, bulletbit, bullet[bullet_count].xpos, bullet[bullet_count].ypos);
                            
                            bullet_count++;         //add one to the bullet count 
                    }
                }
    		
    		textprintf_ex(buffer, font, 0,0, makecol(255,255,255), -1, "kills: %d", bullet_num);
    		if(((bullet_num/bullet_accuracy)*100)>0)
            textprintf_ex(buffer, font, 480,0, makecol(255,255,255), -1, "accuracy: %2.5f %%", ((bullet_num/bullet_accuracy)*100));
    		
    		
    		for(x=0;x<100;x++){
                     if(bullet[x].ypos < 0){        //if the bullet has gone off the top of the screen then make it inactive 
                             bullet[x].active = FALSE;
                             
                     }
                }
    		
    		for(x=0;x<100;x++){
                   if(invada[x].ypos>480){      //if the invader goes off the bottom of the screen move it back up to the top with a random x position
                         invada[x].ypos= 0;
                         invada[x].xpos=rand() % 600 +1;
                   }
            }
    		
            if(background_y_position>480){      //if the background gets to the bottom move it back up to the top
                 background_y_position= -480;
                
                 }
            
            background1_y_position = background_y_position - 960;       //keep the second background inline with the first 
            
            if(background1_y_position>480){     //when the second background gets to the bottom, move it back up to the top
                 background1_y_position= -1440;
                
                 }     
            
    		if(show_bbox == TRUE)         //when the user has pressed the space key and wishes to see the BITMAPS with bounding boxes 
    		{
    			//create the bounding box for the plane
    			line(buffer, plane_bb_left, plane_bb_top, plane_bb_right, plane_bb_top, makecol(255,0,0));
    			line(buffer, plane_bb_left, plane_bb_bottom, plane_bb_right, plane_bb_bottom, makecol(255,0,0));
    			line(buffer, plane_bb_left, plane_bb_top, plane_bb_left, plane_bb_bottom, makecol(255,0,0));
    			line(buffer, plane_bb_right, plane_bb_top, plane_bb_right, plane_bb_bottom, makecol(255,0,0));
    
    			for(x=0;x<100;x++){      //for loop to create the bounding box for the array of invaders
                           line(buffer, invada[x].bb_left, invada[x].bb_top, invada[x].bb_right, invada[x].bb_top, makecol(255,0,0));
    	                   line(buffer, invada[x].bb_left, invada[x].bb_bottom, invada[x].bb_right, invada[x].bb_bottom, makecol(255,0,0));
               			   line(buffer, invada[x].bb_left, invada[x].bb_top, invada[x].bb_left, invada[x].bb_bottom, makecol(255,0,0));
               			   line(buffer, invada[x].bb_right, invada[x].bb_top, invada[x].bb_right, invada[x].bb_bottom, makecol(255,0,0));
                }
             }
    		
            
            shoot_time++;
            
            blit(buffer, screen, 0, 0, 0, 0, 640, 480);         //clear the buffer, and the screen 
    		clear(buffer);
            }
            }
    //destroy all the bitmaps     
    destroy_bitmap(buffer);
	destroy_bitmap(plane);
	destroy_bitmap(invader);
	destroy_bitmap(gameover);
	destroy_bitmap(background);
	destroy_bitmap(background1);
	destroy_bitmap(intro);
	return 0;

}
END_OF_MAIN()


