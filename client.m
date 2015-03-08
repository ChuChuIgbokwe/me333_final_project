function client(port)
%   provides a menu for accessing PIC32 motor control functions
%
%   client_menu(port)
%
%   Input Arguments:
%       port - the name of the com port.  This should be the same as what
%               you use in screen or putty in quotes ' '
%
%   Example:
%       client_menu('/dev/ttyUSB0') (Linux/Mac)
%       client_menu('COM3') (PC)
%
%   For convenience, you may want to embed this in a script that
%   contains your port number
   
% Opening COM connection
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

fprintf('Opening port %s....\n',port);

% settings for opening the serial port. baud rate 230400, hardware flow control
% wait up to 120 seconds for data before timing out
mySerial = serial(port, 'BaudRate', 230400, 'FlowControl', 'hardware','Timeout',120); 
% opens serial connection
fopen(mySerial);
% closes serial port when function exits
clean = onCleanup(@()fclose(mySerial));                                 

has_quit = false;
% menu loop
while ~has_quit
    % display the menu options
    fprintf('d: Dummy Command    f: Sum 2 numbers\nr: Count encoder ticks    a: Motor angle    i: Reset encoder\nq: Quit\n');
    % read the users choice
    selection = input('Enter Command: ', 's');
     
    % send the command to the PIC32
    fprintf(mySerial,'%c\n',selection);

    
    % take the appropriate action
    switch selection
        case 'd'                                    % example operation
            n = input('Enter number: ');            % get the number to send
            fprintf(mySerial, '%d\n',n);            % send the number
            n = fscanf(mySerial,'%d');
            fprintf('Read: %d\n',n);
        case 'f'                                    % example operation
            n = input('Enter the first number: ');  % get the first number to send
            fprintf(mySerial, '%d\n',n);            % send the number
            n = input('Enter the second number: '); % get the second number to send
            fprintf(mySerial, '%d\n',n);            % send the number
            n = fscanf(mySerial,'%d');
            fprintf('Read: %d\n',n);
        case 'r'                                    % read number of ticks
            n = fscanf(mySerial,'%d');
            fprintf('Number of ticks: %d\n',n);
        case 'a'                                    % read angle
            n = fscanf(mySerial,'%d');
            fprintf('The rotor angle in deg/10: %d\n',n);
        case 'i'                                    % reset encoder
            fprintf('Encoder reseted\n');
        case 'q'
          has_quit = true;              % exit matlab
        otherwise
            fprintf('Invalid Selection %c\n', selection);
    end
end

end
