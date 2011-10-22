echo "Updating floppy image..."
sudo /sbin/losetup /dev/loop0 kaos.img
sudo mkdir mnt
sudo mount /dev/loop0 mnt
sudo cp ../kernel.bin mnt/kernel.bin
sudo cp menu.lst mnt/boot/grub/menu.lst
sudo umount /dev/loop0
sudo /sbin/losetup -d /dev/loop0
sudo rmdir mnt
echo "Done!"
