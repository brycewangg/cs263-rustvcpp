use std::thread;

fn increment() {
    let mut counter:f64 = 0.0;
    let mut i:i32 = 0;
    while i < 1000000000 {
        counter += 1.0;
        i += 1;
    }

    println!("Counter is: {}", counter);
}

fn main() {
    let mut handles = vec![];

    let mut i:i32 = 0;
    while i < 1000 {
        let handle = thread::spawn( || {
            increment();
        });
        handles.push(handle);
        i += 1;
    }

    for handle in handles {
        handle.join().unwrap();
    }
}