package com.example.myapplication ;

import androidx.appcompat.app.AppCompatActivity;

import android.app.DatePickerDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    EditText editTextName;
    TextView textViewResult, textViewDOB;
    RadioGroup radioGroupGender;
    Spinner spinnerCountry;
    CheckBox checkBoxConfirm;
    ProgressBar progressBar;
    Button buttonCalculate;

    int dobDay, dobMonth, dobYear;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editTextName = findViewById(R.id.editTextName);
        textViewResult = findViewById(R.id.textViewResult);
        textViewDOB = findViewById(R.id.textViewDOB);
        radioGroupGender = findViewById(R.id.radioGroupGender);
        spinnerCountry = findViewById(R.id.spinnerCountry);
        checkBoxConfirm = findViewById(R.id.checkBoxConfirm);
        progressBar = findViewById(R.id.progressBar);
        buttonCalculate = findViewById(R.id.buttonCalculate);

        // Setup Spinner
        String[] countries = {"USA", "India", "Canada", "Germany", "Australia"};
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_dropdown_item, countries);
        spinnerCountry.setAdapter(adapter);

        // Default to today for DOB
        final Calendar calendar = Calendar.getInstance();
        dobDay = calendar.get(Calendar.DAY_OF_MONTH);
        dobMonth = calendar.get(Calendar.MONTH);
        dobYear = calendar.get(Calendar.YEAR);

        textViewDOB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                DatePickerDialog datePickerDialog = new DatePickerDialog(MainActivity.this,
                        new DatePickerDialog.OnDateSetListener() {
                            @Override
                            public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
                                dobDay = dayOfMonth;
                                dobMonth = month;
                                dobYear = year;
                                textViewDOB.setText(dayOfMonth + "/" + (month + 1) + "/" + year);
                            }
                        }, dobYear, dobMonth, dobDay);
                datePickerDialog.show();
            }
        });

        buttonCalculate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                calculateAge();
            }
        });
    }

    private void calculateAge() {
        String name = editTextName.getText().toString().trim();
        if (name.isEmpty()) {
            Toast.makeText(this, "Please enter your name", Toast.LENGTH_SHORT).show();
            return;
        }

        int selectedGenderId = radioGroupGender.getCheckedRadioButtonId();
        if (selectedGenderId == -1) {
            Toast.makeText(this, "Please select gender", Toast.LENGTH_SHORT).show();
            return;
        }
        RadioButton selectedGender = findViewById(selectedGenderId);

        if (textViewDOB.getText().toString().equals("Select Date of Birth")) {
            Toast.makeText(this, "Please select date of birth", Toast.LENGTH_SHORT).show();
            return;
        }

        if (!checkBoxConfirm.isChecked()) {
            Toast.makeText(this, "Please confirm your information", Toast.LENGTH_SHORT).show();
            return;
        }

        String country = spinnerCountry.getSelectedItem().toString();

        Calendar today = Calendar.getInstance();
        int age = today.get(Calendar.YEAR) - dobYear;
        if (today.get(Calendar.MONTH) < dobMonth ||
                (today.get(Calendar.MONTH) == dobMonth && today.get(Calendar.DAY_OF_MONTH) < dobDay)) {
            age--;
        }

        progressBar.setVisibility(View.VISIBLE);
        progressBar.setProgress(0);
        progressBar.setProgress(100);

        String result = "Hello " + name + "!\n"
                + "Gender: " + selectedGender.getText().toString() + "\n"
                + "Country: " + country + "\n"
                + "Your age is: " + age + " years";

        textViewResult.setText(result);
        Toast.makeText(this, "Age Calculated!", Toast.LENGTH_SHORT).show();
        progressBar.setVisibility(View.GONE);
    }
}
