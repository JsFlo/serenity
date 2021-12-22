#include <LibCore/System.h>
#include <LibGUI/Application.h>
#include <LibGUI/BoxLayout.h>
#include <LibGUI/Button.h>
#include <LibGUI/Frame.h>
#include <LibGUI/MessageBox.h>
#include <LibMain/Main.h>
#include <unistd.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    TRY(Core::System::pledge("stdio recvfd sendfd rpath wpath cpath unix"));

    auto app = GUI::Application::construct(arguments.argc, arguments.argv);

    TRY(Core::System::pledge("stdio recvfd sendfd rpath"));

    auto window = GUI::Window::construct();
    window->set_title("Form1");
    window->resize(96, 44);
    window->set_resizable(false);

    auto& main_widget = window->set_main_widget<GUI::Widget>();
    main_widget.set_fill_with_background_color(true);

    auto& layout = main_widget.set_layout<GUI::VerticalBoxLayout>();
    layout.set_margins(16);

    auto& button = main_widget.add<GUI::Button>("Click me!");
    button.on_click = [&](auto) {
        GUI::MessageBox::show(window, "Hello friends!", ":^)");
    };

    window->show();
    return app->exec();
}
