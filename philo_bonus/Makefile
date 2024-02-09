define HEADER

                                ..                                
                              ...                                 
                      ..........................                  
                   ................................               
                     .................................            
                   .....................................          
                  ........................................        
                .............................................     
               ................................................   
              ...............................................     
              ................................................    
              ................................................    
              .................................................   
              ....................................-............   
              ...................--...............+#...........   
              ...................##...............###...........  
             ...................+###.............+###+..........  
                ...............+#####...........-+####-....... .. 
                 ..+##........+##+++--...............-#.......    
                  .####......+#-....--#-......+-.....+#-......    
 ...---           .+####+.....#-.......#+..#.##-++-+-###.....     
 .++++-..+-.........+######...##-+++++-#########..-+####.. .      
 -+++++++..............-++####+#########################-                           _
.+++++++.....................-##############+####+-..-+++-                         | |            __
.++++++-.........................-++#########+-+-++++++++.        _______ __ __  __| | ____      |__| ____   ______
.++++++-...............................++.....-+++++++++-         \_  __ \  |  \/ __ |/ __ \_____|  |/ __ \ /  ___/ 
 .+++++-......................................++++++++++.          |  | \/  |  / /_/ \  ___/_____/  \  ___/ \___ \  
    .-++.....................................++++++++++.           |__|  |____/\____ |\___  >/\__|  |\___  >____  > 
         ..................................#-+++++++++-                             \/    \/ \______|    \/     \/          

=======================================================================================================================
endef
export HEADER

define LIB_HEADER

                            __ __ __                  __ __ __                     __              
.----.-----.--------.-----.|__|  |__|.-----.-----.   |  |__|  |--.----.---.-.----.|__|.-----.-----.
|  __|  _  |        |  _  ||  |  |  ||     |  _  |   |  |  |  _  |   _|  _  |   _||  ||  -__|__ --|
|____|_____|__|__|__|   __||__|__|__||__|__|___  |   |__|__|_____|__| |___._|__|  |__||_____|_____|
                    |__|                   |_____|                                                 

endef
export LIB_HEADER

define APP_HEADER

                           __ __ __                        __    __ __                         __                     
.----.-----.--------.-----|__|  |__.-----.-----.    .-----|  |--|__|  .-----.-----.-----.-----|  |--.-----.----.-----.
|  __|  _  |        |  _  |  |  |  |     |  _  |    |  _  |     |  |  |  _  |__ --|  _  |  _  |     |  -__|   _|__ --|
|____|_____|__|__|__|   __|__|__|__|__|__|___  |    |   __|__|__|__|__|_____|_____|_____|   __|__|__|_____|__| |_____|
                    |__|                 |_____|    |__|                                |__|                          

endef
export APP_HEADER

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = 	philosophers \
		utils/app_init \
		utils/events_handler \
		utils/exit_handler \
		utils/ft_utils_atoitoa \
		utils/ft_utils_mem \
		utils/ft_utils_str \
		utils/garbagecollector_cleaner \
		utils/garbagecollector \
		utils/hypervisor \
		utils/parser \
		utils/simulation \
		utils/struct_init \
		utils/time_utils \

CFILES = $(SRC:%=./%.c)

NAME = philo_bonus

all: $(NAME)

debug: fclean $(CFILES)
	@echo "$$APP_HEADER"
	@printf "\t🤖 Compiling $(NAME)...\r"
	@$(CC) -g3 -pthread -fsanitize=thread $(CFILES) $(CFLAGS) -o $(NAME)
	@printf "\33[2K"
	@echo "\t[INFO]\t[$(NAME)]\t$(NAME) is compiled ✅"
	@echo "\nThe programm was compiled with debug sanitizer set to address\nDo not forget to use \"leak -atExit -- $(NAME)\" in order to check for potential leaks.\nNote that it won't work with the debug version.\n\nFor better debug, you can use \"lldb $(name) <args>\" after using debug rule.\n\n"
	@echo $(shell norminette)

clean:
	@echo "\t[INFO]\t[$(NAME)]\tNothing needs to be cleaned !"

fclean:
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@echo "\t[INFO]\t[$(NAME)]\t$(NAME) is fully deleted 🗑️"
	@echo "\t[INFO]\t[$(NAME)]\t$(BONUS_NAME) is fully deleted 🗑️"

re: fclean all

help:
	@echo "$$HEADER"
	@echo "all		-	Build $(NAME)"
	@echo "clean		-	Clean temporary files"
	@echo "fclean		-	Clean the whole build"
	@echo "debug		-	Runs the program with g3 fsanitize=address"
	@echo "$(NAME)	-	Build the $(NAME) with necessary libs"

$(CFILES): header

%.o: %.c
	@printf "\t🤖 Compiling $<...\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\33[2K"

$(NAME): $(CFILES)
	@echo "$$APP_HEADER"
	@printf "\t🤖 Compiling $(NAME)...\r"
	@$(CC) $(CFILES) $(CFLAGS) -o $(NAME)
	@printf "\33[2K"
	@echo "\t[INFO]\t[$(NAME)]\t$(NAME) is compiled ✅\n"

header:
	@echo "$$HEADER"

.PHONY = all clean fclean re header help
