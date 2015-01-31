// dear rust. yes I would like to use you. thank you. -andy
#![feature(plugin)]
#![feature(hash)]
#![feature(std_misc)]
#![feature(core)]
#![feature(io)]
#![feature(os)]
#![feature(path)]
#![feature(collections)]

#[plugin]
extern crate glium_macros;

extern crate glutin;

#[macro_use]
extern crate glium;

extern crate groove;
extern crate math3d;

mod gui;
use gui::Gui;

use glium::{Surface, Display, DisplayBuild};

use glutin::Event;
use glutin::VirtualKeyCode;

use std::vec::Vec;
use std::option::Option;
use std::result::Result;
use std::thread::Thread;
use std::sync::Arc;
use std::sync::RwLock;
use std::default::Default;

use math3d::{Matrix4, Vector3};

fn main() {
    let mut stderr = &mut std::old_io::stderr();
    let args = std::os::args_as_bytes();
    let exe = String::from_utf8_lossy(args[0].as_slice());

    if args.len() != 2 {
        print_usage(stderr, exe.as_slice());
        std::os::set_exit_status(1);
        return;
    }
    let input_path = Path::new(args[1].as_slice());

    let waveform = Waveform::new(input_path);


    // building the display, ie. the main object
    let display = glutin::WindowBuilder::new()
        .with_title(String::from_str("genesis"))
        .build_glium()
        .unwrap();

    let mut gui = Gui::new(&display);
    let mut label = gui.create_label();
    label.set_color(1.0, 1.0, 1.0, 1.0);
    label.set_text(String::from_str("abcdefghijklmnopqrstuvwxyz"));
    label.update();

    let mut projection = recalc_projection(&display);
    let mut offset_x = 100.0;
    let mut offset_y = 100.0;

    'main: loop {
        // polling and handling the events received by the window
        for event in display.poll_events() {
            match event {
                Event::Closed => break 'main,
                Event::KeyboardInput(_, _, Some(key_code)) => {
                    match key_code {
                        VirtualKeyCode::Escape => break 'main,
                        VirtualKeyCode::Left => {
                            offset_x -= 1.0;
                        },
                        VirtualKeyCode::Right => {
                            offset_x += 1.0;
                        },
                        VirtualKeyCode::Up => {
                            offset_y -= 1.0;
                        },
                        VirtualKeyCode::Down => {
                            offset_y += 1.0;
                        },
                        _ => (),
                    }
                },
                Event::Resized(_, _) => {
                    projection = recalc_projection(&display);
                },
                _ => (),
            }
        }

        let model = Matrix4::identity().translate(offset_x, offset_y, 0.0);
        let mvp = projection.mult(&model);

        // drawing a frame
        let mut target = display.draw();
        target.clear_color(0.3, 0.3, 0.3, 1.0);
        label.draw(&mut target, &mvp);
        waveform.read().unwrap().draw(&mut target, &mvp);
        target.finish();
    }
}

fn recalc_projection(display: &Display) -> Matrix4 {
    let (w, h) = display.get_framebuffer_dimensions();
    Matrix4::ortho(0.0, w as f32, h as f32, 0.0)
}

fn print_usage(stderr: &mut std::old_io::LineBufferedWriter<std::old_io::stdio::StdWriter>, exe: &str) {
    let _ = write!(stderr, "Usage: {} <file>\n", exe);
}

enum WaveformLoadState {
    Error,
    Spawning,
    Opening,
    Reading,
    Complete,
}

struct Waveform {
    buffers: Vec<groove::DecodedBuffer>,
    load_state: WaveformLoadState,
}

impl Waveform {
    fn new(path: Path) -> Arc<RwLock<Self>> {
        let waveform_arc = Arc::new(RwLock::new(Waveform {
            load_state: WaveformLoadState::Spawning,
            buffers: Vec::new(),
        }));
        let waveform_rw = waveform_arc.clone();
        Thread::spawn(move || {
            let set_load_state = |&: state: WaveformLoadState| {
                let mut waveform = waveform_rw.write().unwrap();
                waveform.load_state = state;
            };
            set_load_state(WaveformLoadState::Opening);
            let file = match groove::File::open(&path) {
                Option::Some(f) => f,
                Option::None => {
                    set_load_state(WaveformLoadState::Error);
                    panic!("unable to open file");
                },
            };
            set_load_state(WaveformLoadState::Reading);

            let playlist = groove::Playlist::new();
            let sink = groove::Sink::new();
            sink.set_audio_format(groove::AudioFormat {
                sample_rate: 44100,
                channel_layout: groove::ChannelLayout::LayoutStereo,
                sample_fmt: groove::SampleFormat {
                    sample_type: groove::SampleType::Dbl,
                    planar: false,
                },
            });
            match sink.attach(&playlist) {
                Result::Ok(_) => {},
                Result::Err(_) => {
                    set_load_state(WaveformLoadState::Error);
                    panic!("error attaching sink");
                }
            }
            playlist.append(&file, 1.0, 1.0);

            loop {
                match sink.buffer_get_blocking() {
                    Option::Some(decoded_buffer) => {
                        let mut waveform = waveform_rw.write().unwrap();
                        waveform.buffers.push(decoded_buffer);
                    },
                    Option::None => break,
                }
            }
            set_load_state(WaveformLoadState::Complete);
        });
        waveform_arc
    }

    pub fn draw(&self, frame: &mut glium::Frame, matrix: &Matrix4) {
        //println!("waveform display");
    }
}
