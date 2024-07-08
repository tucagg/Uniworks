# Variables
JAVAC = javac
JAVA = java
SRC_DIR = src
BIN_DIR = bin

# Source files - src dizinindeki tüm java dosyalarını bulur (tüm alt dizinlerle birlikte)
SRC_FILES = $(shell find $(SRC_DIR) -name "*.java")

# Class files - src dizinindeki tüm java dosyalarının bin klasöründe derlenmiş class dosyaları olarak eşleşmesini sağlar
CLASS_FILES = $(patsubst $(SRC_DIR)/%.java,$(BIN_DIR)/%.class,$(SRC_FILES))

# Default target
default: compile run

# Compile all .java files to .class files
compile: $(CLASS_FILES)

# Pattern rule to compile .java files to .class files
$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	@mkdir -p $(dir $@)
	$(JAVAC) -cp $(SRC_DIR) -d $(BIN_DIR) $<

# Run the Main class
run: compile
	$(JAVA) -cp $(BIN_DIR) Main

# Clean up .class files
clean:
	@rm -rf $(BIN_DIR)

.PHONY: default compile run clean
