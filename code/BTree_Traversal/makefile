CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

BUILD_DIR = build

TARGET = $(BUILD_DIR)/main

SOURCES = main.cpp

OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))


all: $(TARGET)

# 链接规则：如何从目标文件(.o)生成最终的可执行文件
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build finished. Run with ./${TARGET}"

# 编译规则：如何从源文件(.cpp)生成目标文件(.o)
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)


clean:
	@echo "Cleaning up build directory..."
	rm -rf $(BUILD_DIR)
	@echo "Clean complete."

# 伪目标定义
.PHONY: all clean