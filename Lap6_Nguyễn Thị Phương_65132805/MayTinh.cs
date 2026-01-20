using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lap6
{
    abstract class MayTinh
    {
        public string NhanHieu { get; set; }
        public int Ram { get; set; }
        public int BoNho { get; set; }
        public float GiaNhap { get; set; }

        public MayTinh() { }

        public MayTinh(string nh, int ram, int boNho, float giaNhap)
        {
            NhanHieu = nh;
            Ram = ram;
            BoNho = boNho;
            GiaNhap = giaNhap;
        }

        public virtual void Nhap()
        {
            Console.Write("Nhập nhãn hiệu: ");
            NhanHieu = Console.ReadLine();

            Console.Write("Nhập RAM (GB): ");
            int ram; // Declare the variable 'ram' here
            while (!int.TryParse(Console.ReadLine(), out ram) || ram <= 0)
                Console.Write("Nhập lại RAM > 0: ");
            Ram = ram;

            Console.Write("Nhập bộ nhớ (GB): ");
            int boNho; // Declare the variable 'boNho' here
            while (!int.TryParse(Console.ReadLine(), out boNho) || boNho <= 0)
                Console.Write("Nhập lại bộ nhớ > 0: ");
            BoNho = boNho;

            Console.Write("Nhập giá nhập: ");
            float gia; // Declare the variable 'gia' here
            while (!float.TryParse(Console.ReadLine(), out gia) || gia <= 0)
                Console.Write("Nhập lại giá nhập > 0: ");
            GiaNhap = gia;
        }


        public abstract float TinhGiaBan();

        public virtual void Xuat()
        {
            Console.WriteLine($"Nhãn hiệu: {NhanHieu}, RAM: {Ram}GB, Bộ nhớ: {BoNho}GB, Giá bán: {TinhGiaBan():F2}");
        }
    }

    // Lớp Laptop kế thừa MayTinh
    class Laptop : MayTinh
    {
        public float TrongLuong { get; set; }

        public Laptop() { }

        public override void Nhap()
        {
            base.Nhap();
            Console.Write("Nhập trọng lượng (kg): ");
            float tl; // Declare the variable 'tl' here
            while (!float.TryParse(Console.ReadLine(), out tl) || tl <= 0)
                Console.Write("Nhập lại trọng lượng > 0: ");
            TrongLuong = tl;
        }


        public override float TinhGiaBan()
        {
            if (TrongLuong >= 2)
                return GiaNhap + GiaNhap * 0.15f;
            else
                return GiaNhap + GiaNhap * 0.20f;
        }

        public override void Xuat()
        {
            base.Xuat();
            Console.WriteLine($"Loại: Laptop, Trọng lượng: {TrongLuong}kg");
        }
    }

    // Lớp Macbook kế thừa MayTinh
    class Macbook : MayTinh
    {
        public string LoaiMac { get; set; }

        public Macbook() { }

        public override void Nhap()
        {
            base.Nhap();

            Console.Write("Nhập loại Macbook (Air / Pro 13 / Pro 16): ");
            LoaiMac = Console.ReadLine();
        }

        public override float TinhGiaBan()
        {
            switch (LoaiMac.ToLower())
            {
                case "air":
                case "macbook air":
                    return GiaNhap * 1.5f;
                case "pro 13":
                case "macbook pro 13":
                    return GiaNhap * 1.8f;
                case "pro 16":
                case "macbook pro 16":
                    return GiaNhap * 2.0f;
                default:
                    return GiaNhap * 1.5f; // mặc định như Air
            }
        }

        public override void Xuat()
        {
            base.Xuat();
            Console.WriteLine($"Loại: Macbook, Phiên bản: {LoaiMac}");
        }
    }
}
