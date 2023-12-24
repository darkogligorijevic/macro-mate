package com.sb.MacroMate;

import androidx.activity.result.ActivityResultLauncher;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import android.Manifest;

import com.journeyapps.barcodescanner.ScanContract;
import com.journeyapps.barcodescanner.ScanOptions;

import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class MainActivity extends AppCompatActivity {



    Socket s;
    InputStreamReader streamReader;
    PrintWriter out;
    EditText etCommand;
    EditText etIP;
    EditText etPort;
    String ip;
    int port;





    private int currentRequestCode;
    private ImageButton currentButtonToUpdate;

    private static final int GALLERY_REQUEST_CODE = 1001;
    private static final int CAMERA_REQUEST_CODE = 1002;
    boolean needsAuthentication = false;
    public ImageButton ibDugme1;
    public ImageButton ibDugme2;
    public ImageButton ibDugme3;
    public ImageButton ibDugme4;
    public ImageButton ibDugme5;
    public ImageButton ibDugme6;
    public ImageButton ibDugme7;
    public ImageButton ibDugme8;
    public ImageButton ibDugme9;
    public ImageButton ibDugme10;
    public ImageButton ibDugme11;
    public ImageButton ibDugme12;
    public ImageButton ibDugme13;
    public ImageButton ibDugme14;
    public ImageButton ibDugme15;

    public Button btPovezi;
    public Button btScanQR;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        setContentView(R.layout.activity_main);







        // Your condition to determine if authentication/setup is needed

            etIP = findViewById(R.id.etIP);
            etPort = findViewById(R.id.etPort);



            btScanQR = findViewById(R.id.btScanQR);
            btPovezi = findViewById(R.id.btPovez);
            ibDugme1 = findViewById(R.id.ibDugme1);
            ibDugme2 = findViewById(R.id.ibDugme2);
            ibDugme3 = findViewById(R.id.ibDugme3);
            ibDugme4 = findViewById(R.id.ibDugme4);
            ibDugme5 = findViewById(R.id.ibDugme5);
            ibDugme6 = findViewById(R.id.ibDugme6);
            ibDugme7 = findViewById(R.id.ibDugme7);
            ibDugme8 = findViewById(R.id.ibDugme8);
            ibDugme9 = findViewById(R.id.ibDugme9);
            ibDugme10 = findViewById(R.id.ibDugme10);
            ibDugme11 = findViewById(R.id.ibDugme11);
            ibDugme12 = findViewById(R.id.ibDugme12);
            ibDugme13 = findViewById(R.id.ibDugme13);
            ibDugme14 = findViewById(R.id.ibDugme14);
            ibDugme15 = findViewById(R.id.ibDugme15);




            int numberOfButtons = 15;

        for (int i = 1; i <= numberOfButtons; i++) {


            try {
                int buttonId = getResources().getIdentifier("ibDugme" + i, "id", getPackageName());
                ImageButton imageButton = findViewById(buttonId);

                String idDugmetaNazivSlike = imageButton.getId() + ".png";
                Log.i("Naziv FOTKE", idDugmetaNazivSlike);
                String imageFileName = idDugmetaNazivSlike;


                FileInputStream inputStream = openFileInput(imageFileName);
                Bitmap savedBitmap = BitmapFactory.decodeStream(inputStream);
                inputStream.close();


                imageButton.setImageBitmap(savedBitmap);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }




        new Thread(new Runnable() {
            public void run() {
                btPovezi.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        ip = etIP.getText().toString();
                        if (!etPort.getText().toString().equals(null) && !etPort.getText().toString().equals("")){
                            try{
                                port = Integer.parseInt(etPort.getText().toString());
                            }catch (Exception e){
                                Log.e("PORT", "onClick: NO INT VALUE", e);
                            }

                        }

                        runSocket();

                    }
                });
            }
        }).start();

        //SOKET









//        //LONG PRESS SLIKA
//        ibDugme1.setOnLongClickListener(new View.OnLongClickListener() {
//            @Override
//            public boolean onLongClick(View v) {
////                if (ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission.CAMERA)
////                        != PackageManager.PERMISSION_GRANTED) {
////                    ActivityCompat.requestPermissions(MainActivity.this,
////                            new String[]{Manifest.permission.CAMERA}, CAMERA_REQUEST_CODE);
////                } else {
//                    openGalleryOrCamera();
////                }
//                return true; // Return true to consume the long click event
//            }
//        });

        View.OnLongClickListener onLongClickListener = new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                if (ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission.CAMERA)
                        != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(MainActivity.this,
                            new String[]{Manifest.permission.CAMERA}, CAMERA_REQUEST_CODE);
                } else {
                    currentButtonToUpdate = (ImageButton) v;
                    if (v.getId() == R.id.ibDugme1) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme2) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme3) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme4) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme5) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme6) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme7) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme8) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme9) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme10) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme11) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme12) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme13) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme14) {
                        currentRequestCode = GALLERY_REQUEST_CODE;
                    } else if (v.getId() == R.id.ibDugme15) {
                        currentRequestCode = GALLERY_REQUEST_CODE;

                    }
                    // Set other request codes for different buttons similarly
                    openGalleryOrCamera();
                }
                return true; // Return true to consume the long click event
            }
        };

        ibDugme1.setOnLongClickListener(onLongClickListener);
        ibDugme2.setOnLongClickListener(onLongClickListener);
        ibDugme3.setOnLongClickListener(onLongClickListener);
        ibDugme4.setOnLongClickListener(onLongClickListener);
        ibDugme5.setOnLongClickListener(onLongClickListener);
        ibDugme6.setOnLongClickListener(onLongClickListener);
        ibDugme7.setOnLongClickListener(onLongClickListener);
        ibDugme8.setOnLongClickListener(onLongClickListener);
        ibDugme9.setOnLongClickListener(onLongClickListener);
        ibDugme10.setOnLongClickListener(onLongClickListener);
        ibDugme11.setOnLongClickListener(onLongClickListener);
        ibDugme12.setOnLongClickListener(onLongClickListener);
        ibDugme13.setOnLongClickListener(onLongClickListener);
        ibDugme14.setOnLongClickListener(onLongClickListener);
        ibDugme15.setOnLongClickListener(onLongClickListener);


    }




//    public void ServerStart(String ipp, int portt){
//        new Thread(new Runnable() {
//            public void run() {
//
//
//                        Log.d("IP AND PORT", "IP: " + ipp + " PORT: " + portt);
//                        new Thread(new Runnable() {
//                            public void run() {
//                                try {
//                                    s = new Socket(etIP.getText().toString(), port);
//                                    streamReader = new InputStreamReader(s.getInputStream());
//                                    out = new PrintWriter(s.getOutputStream(),true);
//                                    //TESTIRANJE
//                                    ibDugme1.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random1");
//                                        }
//                                    });
//
//                                    ibDugme2.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random2");
//                                        }
//                                    });
//
//                                    ibDugme3.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random3");
//                                        }
//                                    });
//
//                                    ibDugme4.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random4");
//                                        }
//                                    });
//
//                                    ibDugme5.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random5");
//                                        }
//                                    });
//
//                                    ibDugme6.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random6");
//                                        }
//                                    });
//
//                                    ibDugme7.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random7");
//                                        }
//                                    });
//
//                                    ibDugme8.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random8");
//                                        }
//                                    });
//
//                                    ibDugme9.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random9");
//                                        }
//                                    });
//
//                                    ibDugme10.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random10");
//                                        }
//                                    });
//
//                                    ibDugme11.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random11");
//                                        }
//                                    });
//
//                                    ibDugme12.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random12");
//                                        }
//                                    });
//
//                                    ibDugme13.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random13");
//                                        }
//                                    });
//
//                                    ibDugme14.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random14");
//                                        }
//                                    });
//
//                                    ibDugme15.setOnClickListener(new View.OnClickListener() {
//                                        public void onClick(View v) {
//                                            stampaj(out, "random15");
//                                        }
//                                    });
//
//                                } catch (UnknownHostException e) {
//                                    System.err.println("Unknown Host.");
//                                    // System.exit(1);
//                                } catch (IOException e) {
//                                    System.err.println("Couldn't get I/O for "
//                                            + "the connection.");
//                                    System.err.println(e);
//                                    //  System.exit(1);
//                                }
//                            }
//                        }).start();
//
//                    }
//
//
//        }).start();
//    }


    private void scanCode() {
        ScanOptions options = new ScanOptions();
        options.setPrompt("Press volume up button to turn flash on");
        options.setBeepEnabled(true);
        options.setOrientationLocked(true);
        options.setCaptureActivity(CaptureAct.class);
        barLauncher.launch(options);
    }

    ActivityResultLauncher<ScanOptions> barLauncher = registerForActivityResult(new ScanContract(), result -> {
        if (result.getContents() != null) {

            String barcodeString = result.getContents();

            String[] separated = barcodeString.split("\\+");

            etIP.setText(separated[0]);

            etPort.setText(separated[1]);


            ip = etIP.getText().toString();
            if (!etPort.getText().toString().equals(null) && !etPort.getText().toString().equals("")){
                try{
                    port = Integer.parseInt(etPort.getText().toString());
                }catch (Exception e){
                    Log.e("PORT", "onClick: NO INT VALUE", e);
                }

            }


            runSocket();



        }
    });


    public void runSocket(){
        new Thread(new Runnable() {
            public void run() {
                try {
                    s = new Socket(etIP.getText().toString(), port);
                    streamReader = new InputStreamReader(s.getInputStream());
                    out = new PrintWriter(s.getOutputStream(),true);
                    //TESTIRANJE
                    ibDugme1.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "0");
                        }
                    });

                    ibDugme2.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "1");
                        }
                    });

                    ibDugme3.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "2");
                        }
                    });

                    ibDugme4.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "3");
                        }
                    });

                    ibDugme5.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "4");
                        }
                    });

                    ibDugme6.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "5");
                        }
                    });

                    ibDugme7.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "6");
                        }
                    });

                    ibDugme8.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "7");
                        }
                    });

                    ibDugme9.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "8");
                        }
                    });

                    ibDugme10.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "9");
                        }
                    });

                    ibDugme11.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "10");
                        }
                    });

                    ibDugme12.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "11");
                        }
                    });

                    ibDugme13.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "12");
                        }
                    });

                    ibDugme14.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "13");
                        }
                    });

                    ibDugme15.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            sendThroughSocket(out, "14");
                        }
                    });

                } catch (UnknownHostException e) {
                    System.err.println("Unknown Host.");
                    // System.exit(1);
                } catch (IOException e) {
                    System.err.println("Couldn't get I/O for "
                            + "the connection.");
                    System.err.println(e);
                    //  System.exit(1);
                }
            }
        }).start();
    }






    public void sendThroughSocket(PrintWriter pw, String komanda){

        new Thread(new Runnable() {
            public void run() {
                out.println(komanda);
            }
        }).start();


    }

    public void sendThroughSocket(PrintWriter pw){

        new Thread(new Runnable() {
            public void run() {
                out.println(etCommand.getText());
            }
        }).start();


    }

    public void etPortClearOnClick(View v){
        etPort.setText("");
    }

    public void etIPClearOnClick(View v){
        etIP.setText("");
    }


    public void onClickQR(View v){
        scanCode();
    }


    private void openGalleryOrCamera() {
        Intent intent;
        if (currentRequestCode == GALLERY_REQUEST_CODE) {
            intent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        } else if (currentRequestCode == CAMERA_REQUEST_CODE) {
            intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        } else {
            // Handle other request codes similarly if needed
            return;
        }

        startActivityForResult(intent, currentRequestCode);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == RESULT_OK) {
            if (requestCode == GALLERY_REQUEST_CODE && data != null) {
                Uri selectedImage = data.getData();
                if (currentButtonToUpdate != null) {
                    currentButtonToUpdate.setImageURI(selectedImage);

                    //POCETAK SAVE-A

                    String idDugmetaNazivSlike = currentButtonToUpdate.getId() + ".png";
                    Log.i("Naziv FOTKE", idDugmetaNazivSlike);
                    String imageFileName = idDugmetaNazivSlike; // Change the filename based on the button ID


                    try {
                        InputStream inputStream = getContentResolver().openInputStream(selectedImage);
                        Bitmap selectedBitmap = BitmapFactory.decodeStream(inputStream);
                        inputStream.close();

                        FileOutputStream outputStream = openFileOutput(imageFileName, Context.MODE_PRIVATE);
                        if(selectedBitmap == null){
                            Log.i("SLIKA", "JE NULL ");
                        }

                        selectedBitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream);
                        outputStream.flush();
                        outputStream.close();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }


                    //KRAJ

                }
            } else if (requestCode == CAMERA_REQUEST_CODE && data != null) {
                Bitmap photo = (Bitmap) data.getExtras().get("data");
                if (currentButtonToUpdate != null) {
                    currentButtonToUpdate.setImageBitmap(photo);


                }
            }
        }
    }


    // Handle permission request results
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == CAMERA_REQUEST_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                openGalleryOrCamera();
            } else {
                Toast.makeText(this, "Camera permission is required to take a picture", Toast.LENGTH_SHORT).show();
            }
        }

    }
}