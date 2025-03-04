use std::thread;

fn increment() {
    let mut counter:f64 = 0.0;
    for _ in 0..100000 {
        counter += 1.0;
    }
}

fn main() {
    let mut handles = vec![];

    for _ in 0..10 {
        let handle = thread::spawn( || {
            increment();
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Threads finished");
}