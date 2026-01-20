using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lap6
{
    interface Ishape
    {
        float DonGia { get; set; }
        float TinhChiPhiVe();
    }
    abstract class Shape
    {
        public string TenHinh { get; set; }

        public Shape() { }

        public Shape(string tenHinh)
        {
            TenHinh = tenHinh;
        }

        public abstract float TinhDienTich();
    }

    // Lớp Rectangle kế thừa Shape, thực thi IPaint, implement IComparable
    class Rectangle : Shape, Ishape, IComparable<Rectangle>
    {
        public float ChieuDai { get; set; }
        public float ChieuRong { get; set; }
        public float DonGia { get; set; }

        public Rectangle() { }

        public void Nhap()
        {
            Console.Write("Nhập tên hình: ");
            TenHinh = Console.ReadLine();

            Console.Write("Nhập chiều dài: ");
            float dai;
            while (!float.TryParse(Console.ReadLine(), out dai) || dai <= 0)
                Console.Write("Nhập lại chiều dài hợp lệ (> 0): ");
            ChieuDai = dai;

            Console.Write("Nhập chiều rộng: ");
            float rong;
            while (!float.TryParse(Console.ReadLine(), out rong) || rong <= 0)
                Console.Write("Nhập lại chiều rộng hợp lệ (> 0): ");
            ChieuRong = rong;

            Console.Write("Nhập đơn giá vẽ: ");
            float dg;
            while (!float.TryParse(Console.ReadLine(), out dg) || dg < 0)
                Console.Write("Nhập lại đơn giá hợp lệ (>= 0): ");
            DonGia = dg;
        }


        public override float TinhDienTich()
        {
            return ChieuDai * ChieuRong;
        }

        public float TinhChiPhiVe()
        {
            return DonGia * TinhDienTich();
        }

        public void Xuat()
        {
            Console.WriteLine($"Tên: {TenHinh}, Diện tích: {TinhDienTich():F2}, Chi phí vẽ: {TinhChiPhiVe():F2}");
        }

        public int CompareTo(Rectangle other)
        {
            return other.TinhChiPhiVe().CompareTo(this.TinhChiPhiVe()); // giảm dần
        }
    }
}
