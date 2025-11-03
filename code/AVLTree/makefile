# 编译器
CXX = g++

# 编译选项 (Flags)
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# 定义输出目录变量
BUILD_DIR = build

# 让最终目标指向 build 目录
TARGET = $(BUILD_DIR)/AVL

# 头文件
HEADERS = AVLTree.hpp

# 源文件列表 (.cpp files)
SOURCES = main.cpp

# 使用 patsubst 函数将 .cpp 文件映射到 build 目录下的 .o 文件
OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))


# "all" 是第一个规则，也是默认规则。
all: $(TARGET)

# 链接规则：如何从目标文件(.o)生成最终的可执行文件
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build finished. Run with ./${TARGET}"

# 编译规则：如何从源文件(.cpp)生成目标文件(.o)
$(BUILD_DIR)/%.o: %.cpp $(HEADERS) | $(BUILD_DIR)
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