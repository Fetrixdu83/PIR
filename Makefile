CC = gcc
CFLAGS = -Wall 

SRC_ROLES = ./src/Roles/src
SRC_SIMULATION = ./src/Simulation

SRCS =  $(SRC_ROLES)/*.c $(SRC_SIMULATION)/simulation.c

TARGET_SIMULATION = sim_jeu

simulation: $(TARGET_SIMULATION)
			./$(TARGET_SIMULATION)

$(TARGET_SIMULATION): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET_SIMULATION)
