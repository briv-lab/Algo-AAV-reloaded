# Makefile pour le projet Algo AAV reloaded

# Variables
CXX = g++
CXXFLAGS = -g -Wall -std=c++17
INCLUDEDIR = include
SRCDIR = src
OBJDIR = obj

# Fichiers sources et objets
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = AlgoAAVReloaded.exe

# Règle principale
all: $(TARGET)

# Compilation du programme principal
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c $< -o $@

# Création du dossier obj s'il n'existe pas
$(OBJDIR):
	mkdir $(OBJDIR)

# Nettoyage
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Reconstruire complètement
rebuild: clean all

.PHONY: all clean rebuild