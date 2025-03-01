const NUM: u32 = 1000000000;

fn main() {
    let mut x: f64 = 1.0;
    for _ in 0..NUM {
        x += 1.0;
    }
    println!("{}", x);
}
