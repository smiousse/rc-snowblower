package io.github.smiousse.rcsnowblower;

import android.annotation.SuppressLint;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.BluetoothLeScanner;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;
import android.content.Context;

import java.util.List;
import java.util.UUID;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 */
public class FullscreenActivity extends AppCompatActivity {
    private static final int REQUEST_ENABLE_BT = 1;
    private BluetoothManager bluetoothManager;
    private Handler mHandler;
    private BluetoothGatt mGatt = null;
    private BluetoothDevice bluetoothDevice;

    private static final String DEVICE_MAC_ADDRESS = "64:33:DB:92:BC:A5";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_fullscreen);

        // Use this check to determine whether BLE is supported on the device. Then
        // you can selectively disable BLE-related features.
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Toast.makeText(this, R.string.ble_not_supported, Toast.LENGTH_SHORT).show();
            finish();
        }

        mHandler = new Handler();
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Toast.makeText(this, "BLE Not Supported", Toast.LENGTH_SHORT).show();
            finish();
        }


        initButtons();


        // Initializes Bluetooth adapter.
        bluetoothManager =
                (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        BluetoothAdapter bluetoothAdapter = bluetoothManager.getAdapter();


        // Ensures Bluetooth is available on the device and it is enabled. If not,
        // displays a dialog requesting user permission to enable Bluetooth.
        if (bluetoothAdapter == null || !bluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }

        bluetoothDevice = bluetoothManager.getAdapter().getRemoteDevice(DEVICE_MAC_ADDRESS);
        if(bluetoothDevice != null){
            Log.i("BluetoothDevice","found device " + bluetoothDevice.getName());
            connectToDevice(bluetoothDevice);
            //sendStop();
        } else {
            Log.e("BluetoothDevice"," CANT find device for " + DEVICE_MAC_ADDRESS);
        }
    }

    private void initButtons(){
        ImageButton forward = (ImageButton) findViewById(R.id.forward);
        forward.setOnTouchListener(new ButtonActionOnTouchListener("F", "S"));

        ImageButton forwardLeft = (ImageButton) findViewById(R.id.forward_left);
        forwardLeft.setOnTouchListener(new ButtonActionOnTouchListener("N", "S"));

        ImageButton forwardRight = (ImageButton) findViewById(R.id.forward_right);
        forwardRight.setOnTouchListener(new ButtonActionOnTouchListener("M", "S"));

        ImageButton backward = (ImageButton) findViewById(R.id.backward);
        backward.setOnTouchListener(new ButtonActionOnTouchListener("B", "S"));

        ImageButton backwardLeft = (ImageButton) findViewById(R.id.backward_left);
        backwardLeft.setOnTouchListener(new ButtonActionOnTouchListener("P", "S"));

        ImageButton backwardRight = (ImageButton) findViewById(R.id.backward_right);
        backwardRight.setOnTouchListener(new ButtonActionOnTouchListener("O", "S"));

        ImageButton left = (ImageButton) findViewById(R.id.full_left);
        left.setOnTouchListener(new ButtonActionOnTouchListener("L", "S"));

        ImageButton right = (ImageButton) findViewById(R.id.full_right);
        right.setOnTouchListener(new ButtonActionOnTouchListener("R", "S"));

    }

    private void connectToDevice(BluetoothDevice device) {
        if (mGatt == null) {
            mGatt = device.connectGatt(this, false, gattCallback);
        }
    }

    private void sendAction(String action){
        if (mGatt != null) {

            BluetoothGattService service = mGatt.getService(UUID.fromString("0000ffe0-0000-1000-8000-00805f9b34fb"));
            BluetoothGattCharacteristic characteristic = service.getCharacteristic(UUID.fromString("0000ffe1-0000-1000-8000-00805f9b34fb"));

            characteristic.setValue(action.getBytes());
            mGatt.writeCharacteristic(characteristic);
        }
    }

    private final BluetoothGattCallback gattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            Log.i("onConnectionStateChange", "Status: " + status);
            switch (newState) {
                case BluetoothProfile.STATE_CONNECTED:
                    Log.i("gattCallback", "STATE_CONNECTED");
                    gatt.discoverServices();
                    break;
                case BluetoothProfile.STATE_DISCONNECTED:
                    Log.e("gattCallback", "STATE_DISCONNECTED");
                    break;
                default:
                    Log.e("gattCallback", "STATE_OTHER");
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {

            List<BluetoothGattService> services = mGatt.getServices();
            Log.i("onServicesDiscovered", services.toString());
            gatt.readCharacteristic(services.get(0).getCharacteristics().get(0));
        }

        @Override
        public void onCharacteristicRead(final BluetoothGatt gatt, final BluetoothGattCharacteristic characteristic, int status) {
            Log.i("onCharacteristicRead", characteristic.toString());
        }
    };

    public class ButtonActionOnTouchListener implements View.OnTouchListener {

        private String onPressAction;
        private String onReleaseAction;

        public ButtonActionOnTouchListener(String onPressAction, String onReleaseAction) {
            this.onPressAction = onPressAction;
            this.onReleaseAction = onReleaseAction;
        }

        @Override
        public boolean onTouch(View v, MotionEvent event) {
            switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    sendAction(onPressAction);
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_CANCEL:
                    sendAction(onReleaseAction);
                    break;
            }
            return false;
        }
    }

}