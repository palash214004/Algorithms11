package com.example.practice2;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView; // Import CardView

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

    // Declare all the UI components
    private EditText etName;
    private CheckBox cbProgramming, cbReading;
    private RadioGroup rgGender;
    private Spinner spinnerCountry;
    private Button btnDatePicker, btnSubmit;
    private ProgressBar progressBar;
    private TextView tvSelectedDate;

    // --- NEW: Declare summary views ---
    private CardView cvProfileSummary;
    private TextView tvSummaryName, tvSummaryGender, tvSummaryInterests, tvSummaryCountry, tvSummaryBirthDate;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize UI components by finding them in the layout
        initializeViews();

        // Setup the Spinner with data
        setupSpinner();

        // Setup click listeners for the buttons
        setupClickListeners();
    }

    private void initializeViews() {
        // Input Views
        tvSelectedDate = findViewById(R.id.tvSelectedDate);
        etName = findViewById(R.id.etName);
        cbProgramming = findViewById(R.id.cbProgramming);
        cbReading = findViewById(R.id.cbReading);
        rgGender = findViewById(R.id.rgGender);
        spinnerCountry = findViewById(R.id.spinnerCountry);
        btnDatePicker = findViewById(R.id.btnDatePicker);
        btnSubmit = findViewById(R.id.btnSubmit);
        progressBar = findViewById(R.id.progressBar);

        // --- NEW: Initialize summary views ---
        cvProfileSummary = findViewById(R.id.cvProfileSummary);
        tvSummaryName = findViewById(R.id.tvSummaryName);
        tvSummaryGender = findViewById(R.id.tvSummaryGender);
        tvSummaryInterests = findViewById(R.id.tvSummaryInterests);
        tvSummaryCountry = findViewById(R.id.tvSummaryCountry);
        tvSummaryBirthDate = findViewById(R.id.tvSummaryBirthDate);
    }

    private void setupSpinner() {
        String[] countries = {"USA", "Canada", "UK", "Germany", "India", "Australia"};
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this,
                android.R.layout.simple_spinner_item, countries);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinnerCountry.setAdapter(adapter);
    }

    private void setupClickListeners() {
        btnDatePicker.setOnClickListener(v -> showDatePickerDialog());

        // The submit button now calls collectAndShowData
        btnSubmit.setOnClickListener(v -> collectAndShowData());
    }

    private void showDatePickerDialog() {
        final Calendar calendar = Calendar.getInstance();
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH);
        int day = calendar.get(Calendar.DAY_OF_MONTH);

        DatePickerDialog datePickerDialog = new DatePickerDialog(this,
                (view, year1, monthOfYear, dayOfMonth) -> {
                    String selectedDate = dayOfMonth + "/" + (monthOfYear + 1) + "/" + year1;
                    tvSelectedDate.setText(selectedDate);
                }, year, month, day);
        datePickerDialog.show();
    }

    // --- MODIFIED: This method now populates and shows the summary card ---
    private void collectAndShowData() {
        // --- Collect Data from all UI Components ---
        String name = etName.getText().toString().trim();
        if (name.isEmpty()) {
            Toast.makeText(this, "Please enter your name", Toast.LENGTH_SHORT).show();
            return; // Stop execution if name is missing
        }

        StringBuilder interestsBuilder = new StringBuilder();
        if (cbProgramming.isChecked()) {
            interestsBuilder.append("Programming, ");
        }
        if (cbReading.isChecked()) {
            interestsBuilder.append("Reading, ");
        }
        String interests = interestsBuilder.toString();
        if (!interests.isEmpty()) {
            interests = interests.substring(0, interests.length() - 2); // Remove trailing comma and space
        } else {
            interests = "None selected";
        }

        int selectedGenderId = rgGender.getCheckedRadioButtonId();
        String gender = "Not selected";
        if (selectedGenderId != -1) {
            RadioButton selectedRadioButton = findViewById(selectedGenderId);
            gender = selectedRadioButton.getText().toString();
        }

        String country = spinnerCountry.getSelectedItem().toString();
        String birthDate = tvSelectedDate.getText().toString();

        // --- Populate the summary TextViews ---
        tvSummaryName.setText("Name: " + name);
        tvSummaryGender.setText("Gender: " + gender);
        tvSummaryInterests.setText("Interests: " + interests);
        tvSummaryCountry.setText("Country: " + country);
        tvSummaryBirthDate.setText("Birth Date: " + birthDate);

        // --- Make the summary CardView visible ---
        cvProfileSummary.setVisibility(View.VISIBLE);

        // Update Progress Bar
        progressBar.setProgress(100);

        // Optional: Show a Toast to confirm submission
        Toast.makeText(this, "Profile Submitted!", Toast.LENGTH_SHORT).show();
    }
}