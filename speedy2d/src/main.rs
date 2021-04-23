use speedy2d::color::Color;
use speedy2d::window::WindowHandler;
use speedy2d::Window;

struct MyWindow {
    time: f64,
}

impl MyWindow {
    fn new() -> MyWindow {
        MyWindow { time: 0.0 }
    }
}

impl WindowHandler for MyWindow {
    fn on_start(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        info: speedy2d::window::WindowStartupInfo,
    ) {
    }

    fn on_user_event(&mut self, helper: &mut speedy2d::window::WindowHelper<()>, user_event: ()) {}

    fn on_resize(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        size_pixels: speedy2d::dimen::Vector2<u32>,
    ) {
    }

    fn on_scale_factor_changed(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        scale_factor: f64,
    ) {
    }

    fn on_draw(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        graphics: &mut speedy2d::Graphics2D,
    ) {
        graphics.clear_screen(Color::BLACK);

        graphics.draw_circle((100.0, 100.0), 40.0, Color::RED);

        helper.request_redraw();
    }

    fn on_mouse_move(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        position: speedy2d::dimen::Vector2<f32>,
    ) {
    }

    fn on_mouse_button_down(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        button: speedy2d::window::MouseButton,
    ) {
    }

    fn on_mouse_button_up(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        button: speedy2d::window::MouseButton,
    ) {
    }

    fn on_key_down(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        virtual_key_code: Option<speedy2d::window::VirtualKeyCode>,
        scancode: speedy2d::window::KeyScancode,
    ) {
    }

    fn on_key_up(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        virtual_key_code: Option<speedy2d::window::VirtualKeyCode>,
        scancode: speedy2d::window::KeyScancode,
    ) {
    }

    fn on_keyboard_char(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        unicode_codepoint: char,
    ) {
    }

    fn on_keyboard_modifiers_changed(
        &mut self,
        helper: &mut speedy2d::window::WindowHelper<()>,
        state: speedy2d::window::ModifiersState,
    ) {
    }
}

fn main() {
    println!("Hello, world!");

    let window = Window::new_centered("Title", (640, 480)).unwrap();

    window.run_loop(MyWindow::new());

    println!("Goodbye, world!");
}
