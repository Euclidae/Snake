#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

enum Direction{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Food{
    //TODO Figure out a system where upon collision with the food,
    //The spawn mechanic is trigger.
    //Sucessful!
    SDL_Rect object;
    int x = 0, y = 0;
    Food(int x = 0, int y = 0): x(x), y(y){
        object = {x, y, 20, 20};
    }

    void spawn(SDL_Renderer* renderer, bool flag = false){
      if(flag){
        object.x = (rand() % 980) + 1;
        object.y = (rand() & 980) - 1;        
    }
              
        SDL_SetRenderDrawColor(renderer,0,255,233,255);
        SDL_RenderFillRect(renderer, &object);
    }
    
};

class Snake{
  private:
    int x, y;
    int dy = 5, dx = 5;
    Direction dir;

    struct Segment {
    SDL_Rect object;
    Segment* next = nullptr;
    Segment* previous = nullptr;

    Segment(int x = 0, int y = 0) {
        object = {x, y, 20, 20};
    }
};

    Segment* head = nullptr;
    Segment* tail = nullptr;

    void extend_serpent(){
		//TODO Implement collision system where this function will be called
    //TODO When snake goes of bounds, the head must emerge from the other side.
    //
        while(tail->next != nullptr){
            tail = tail->next;
        }

        if(dir == Direction::UP){
            tail->next = new Segment(tail->previous->object.x, tail->previous->object.y+20);
            tail->next->previous = tail;
        }
        else if(dir == Direction::DOWN){
            tail->next = new Segment(tail->previous->object.x, tail->previous->object.y-20);
            tail->next->previous = tail;
        }
        else if(dir == Direction::LEFT){
            tail->next = new Segment(tail->previous->object.x+20, tail->previous->object.y);
            tail->next->previous = tail;	
        }
        else if(dir == Direction::RIGHT){
            tail->next = new Segment(tail->previous->object.x-20, tail->previous->object.y);
            tail->next->previous = tail;
        }
        
    }

public:
    Snake(int x, int y) {
        head = new Segment(x, y);
        head->next = new Segment(x - 20, y);
        tail = head->next;
        tail->previous= head;
    }

    void update(float dt, Direction direction) {
    // Update head position
        if (direction == Direction::UP) {
            head->object.y -= dy;
            if(head->object.y <= 0){
                head->object.y = SCREEN_HEIGHT;
            }
        } else if (direction == Direction::DOWN) {
            head->object.y += dy;
            if(head->object.y >= SCREEN_HEIGHT){
                head->object.y = 0;
            }
        } else if (direction == Direction::LEFT) {
            head->object.x -= dx;
            if(head->object.x <= 0){
                head->object.x = SCREEN_WIDTH;
            }
        } else if (direction == Direction::RIGHT) {
            head->object.x += dx;
            if(head->object.x >= SCREEN_WIDTH){
                head->object.x = 0;
            }
        }

        // Update rest of the body
        Segment* current = head;
        int prevX = head->object.x;
        int prevY = head->object.y;
        
        while (current->next != nullptr) {
            int tempX = current->next->object.x;
            int tempY = current->next->object.y;
            current->next->object.x = prevX;
            current->next->object.y = prevY;
            prevX = tempX;
            prevY = tempY;
            current = current->next;
        }
        if(body_collision()){
            reset();
        }
        dir = direction;
}

    void test(){
        //TODO: Use one key to artificially extend snake.
        //Success! Depracated as a result
        extend_serpent();
    }

    void test2(){
        reset();
    }

    void reset() {
        // Delete all segments except the head and the first body segment
        //Successfully created a reset function. Forgot to reset the pointers.
        Segment* current = head->next->next;
        while (current != nullptr) {
            Segment* next = current->next;
            delete current;
            current = next;
        }

        // Reset to initial state (head and one body segment)
        head->next->next = nullptr;
        tail = head->next;

        // Reset direction (assuming UP is the initial direction)
        dir = Direction::UP;
    }

    bool body_collision() {
        Segment* body = head->next->next; // Start from the segment after the first body segment
        while (body != nullptr) {
            
            if (head->object.x == body->object.x && head->object.y == body->object.y) {
                return true; 
            }
            body = body->next;
        }
        return false; 
}

    void render(SDL_Renderer* renderer) {
        Segment* current = head;
        int count = 0;
        while (current != nullptr) {
            if(count != 0)
                SDL_SetRenderDrawColor(renderer, 255, 23, 150, 255);
            else
                SDL_SetRenderDrawColor(renderer, 255, 93, 120, 255);
            SDL_RenderFillRect(renderer, &current->object);
            current = current->next;
            ++count;
        }
}

    bool collision(Food& object){
        //sets up collision system that removes the fruit and extends the snake. 
        //TODO Plan the specifics around this feature
        //TODO Come up with a more effective collision system
        //TODO Fullfilled. Features implemented
        for(int i = 0; i < 20; ++i){
            //iterate to check for x
            for(int j = 0; j < 20; ++j){
                //iterate to check for y
                //first condition checks for basic alignment. Second condition checks if the top x and y of snake make contact. third condition checks if an side of 
                //head makes contact with food.
                if(head->object.x == object.object.x && head->object.y == object.object.y || head->object.x  == object.object.x + i && head->object.y == object.object.y + j
                || head->object.x + i == object.object.x && head->object.y + i == object.object.y + j){
                    extend_serpent();
                    return true;
                }
            }
        }
        
        return false;
    }

	~Snake(){
		tail = head;
		while(tail != nullptr){
			delete tail;
			tail = tail->next;
		}
	}

};

int main() {
    srand(time(0));
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL failed to initialize: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "SDL failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "SDL failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Snake snake(500, 500);
    Food food(700, 700);
    bool running = true;
    SDL_Event event;
    Direction direction = Direction::RIGHT; // Initialize direction
    Direction prevDir = Direction::LEFT;
    while (running) {
       while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_UP:
                        prevDir = direction;
                        direction = Direction::UP;
                        if(prevDir == Direction::DOWN)
                            direction = prevDir; 

                        
                        break;
                    case SDLK_DOWN:
                        prevDir = direction;
                        direction = Direction::DOWN; 

                        if(prevDir == Direction::UP){
                            direction = prevDir;
                        }
                        break;
                    case SDLK_LEFT:
                      prevDir = direction;
                      direction = Direction::LEFT;

                      if(prevDir == Direction::RIGHT){
                            direction = prevDir;
                        } 
                      break;
                    case SDLK_RIGHT:
                        prevDir = direction; 
                        direction = Direction::RIGHT;

                        if(prevDir == Direction::LEFT){
                            direction = prevDir;
                        } 
                        break;
                    
                    case SDLK_w: snake.test(); break;
                    case SDLK_s: snake.reset(); break;
                    default: break;
                }
            }
        }
        //TODO Implement Deltaime 
        //TODO Implement something that stops the snake from going in itself
        snake.update(0.5f, direction); 
    
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        snake.render(renderer);
        if (snake.collision(food)) {
            food.spawn(renderer, true);
        } else {
            food.spawn(renderer, false);
        }
        SDL_RenderPresent(renderer);
		SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
