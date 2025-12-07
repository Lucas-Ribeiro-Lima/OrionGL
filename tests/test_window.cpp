//
// Created by lucaslima on 02/12/2025.
//

#include <gtest/gtest.h>
#include <Window.h>

TEST(Window, correct_inicialization) {
    const oriongl::render::Window w{};
    EXPECT_EQ(w.hasErrors(), 0) << "Window failed to initialize";
}

TEST(Window, glfw_initialization)
{

}

TEST(Window, glad_initialization)
{

}