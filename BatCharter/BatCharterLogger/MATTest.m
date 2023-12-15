close all;
clearvars;

COM = 'COM17';
xmega = serialport(COM,115200,'Timeout',2);
flush(xmega);


    write(xmega, 8, "uint8");
    while xmega.NumBytesAvailable < (4)                                   %Do nothing till data is ready
    end

    RES1 = read(xmega, 1, 'single');
