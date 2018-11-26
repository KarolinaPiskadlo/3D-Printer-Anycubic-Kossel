clear z12 z22 z32 z1 z2 z3

if ~exist('drukarka')
    drukarka=serial('/dev/ttyUSB1')
    drukarka.BaudRate=57600;   
end

try fopen(drukarka)
    catch blad    
end
    
for t = 10:0.1:20
    xc = 0.1 * sin(t) + 0.5;
    yc = 0.1 * cos(t) + 1;
    zc = 0.05 * t;
    clf;
    
    x1 = 0;
    y1 = 0.5;
    x2 = 0;
    y2 = 1.5;
    x3 = 1;
    y3 = 1;
    r = 1;

    if exist('z1')
        z12 = z1;
        z22 = z2;
        z32 = z3;
    end

    col1 = line([0 0],[0.5 0.5],[0 6]);
    col2 = line([0 0],[1.5 1.5],[0 6]);
    col3 = line([1 1],[1 1],[0 6]);

    platform = line(0.5,1,2);

    z1 = zc + sqrt(r^2 - (x1 - xc)^2 - (y1 - yc)^2);
    z2 = zc + sqrt(r^2 - (x2 - xc)^2 - (y2 - yc)^2);
    z3 = zc + sqrt(r^2 - (x3 - xc)^2 - (y3 - yc)^2);

    try
        krok1 = z12 - z1;
        krok2 = z22 - z2;
        krok3 = z32 - z3;
        krok11 = num2str(round(krok1*10000));
        krok21 = num2str(round(krok2*10000));
        krok31 = num2str(round(krok3*10000));
        komunikat = ['x' krok11 ' y' krok21 ' z' krok31 '\n']
        fprintf(drukarka, komunikat)
   
        while (drukarka.BytesAvailable==0)
        end
   
        while (drukarka.BytesAvailable>0)
            fscanf(drukarka);
        end
    
    catch err
        ;
    end

    arm1 = line([x1 xc],[y1 yc],[z1 zc]);
    arm2 = line([x2 xc],[y2 yc],[z2 zc]);
    arm3 = line([x3 xc],[y3 yc],[z3 zc]);

    axis([0 2 0 2 1 3]);
    axis square;

    view(-6,4);
    %pause(0.1);
end