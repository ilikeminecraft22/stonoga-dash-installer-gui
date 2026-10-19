#include <gtkmm-4.0/gtkmm.h>
#include <gtkmm-4.0/gtkmm/label.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>

// Original license -|
//                   |
/*                   V
MIT License

Copyright (c) 2026 Wjanek13

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/ // Thank you Wjanek13 for making the original installer
namespace fs = std::filesystem;

class Window : public Gtk::Window {
public:
    Window() {
        std::cout << "Launched App!\n"
        "Tip: Press \"Verify integrity of game files\" in Steam, to uninstall Stonoga Dash!\n";
        const char* home_path = std::getenv("HOME");
        std::string choice = "?";
        set_title("Stonoga Dash Installer");
        if (home_path == nullptr) {
            std::cout << "error -> could not find home directory\n";
        }
        fs::path path = fs::path(home_path) / ".local/share/Steam/steamapps/common/Geometry Dash/Resources";
        const std::string player_png_name = "player_01-uhd.png";
        set_default_size(400, 250);

        auto* box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);

        box->set_margin(20);

        title_label.set_text("Stonoga Dash Installer");
        title_label.set_markup("<span size='x-large' weight='bold'>Stonoga Dash Installer</span>");

        download_button.set_label("Install Stonoga Dash");
        status_label.set_text("...");
        status_label.set_markup("<span weight='normal' color='#AAAAAA'>...</span>");

        box->append(title_label);
        box->append(download_button);
        box->append(status_label);

        download_button.signal_clicked().connect([this, path, player_png_name]() {
            status_label.set_markup("<span weight='normal' color='#AAAAFF'>Installing</span>");
            try {
                for(const auto& entry : fs::directory_iterator("files/icons")) {
                    if(entry.is_regular_file()) {
                        fs::copy_file(entry.path(), path / "icons" / entry.path().filename(), fs::copy_options::overwrite_existing);
                        std::cout << "added -> " << entry.path().filename().string() << '\n';
                    }
                }

                for (const auto& entry : fs::directory_iterator("files/Resources/dialogIcons")) {
                    if (entry.is_regular_file()) {
                        fs::copy_file(entry.path(), path / entry.path().filename(), fs::copy_options::overwrite_existing);
                        std::cout << "added -> " << entry.path().filename().string() << '\n';
                    }
                }

                for (const auto& entry : fs::directory_iterator("files/Resources/mp3")) {
                    if (entry.is_regular_file()) {
                        fs::copy_file(entry.path(), path / entry.path().filename(), fs::copy_options::overwrite_existing);
                        std::cout << "added -> " << entry.path().filename().string() << '\n';
                    }
                }

                for (const auto& entry : fs::directory_iterator("files/Resources/ogg")) {
                    if (entry.is_regular_file()) {
                        fs::copy_file(entry.path(), path / entry.path().filename(), fs::copy_options::overwrite_existing);
                        std::cout << "added -> " << entry.path().filename().string() << '\n';
                    }
                }
                status_label.set_markup("<span weight='normal' color='#AAFFAA'>Installed!</span>");
            } catch (const fs::filesystem_error& e) {
                std::cout << "Filesystem error: " << e.what() << '\n';
            }
            
        });

        set_child(*box);
    }

private:
    Gtk::Button download_button;
    Gtk::Label title_label;
    Gtk::Label status_label;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("com.stonoga-dash.installer");

    return app->make_window_and_run<Window>(argc, argv);
}