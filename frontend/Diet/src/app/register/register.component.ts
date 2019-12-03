import { Component, OnInit } from '@angular/core';
import { SignInService } from '../sign-in.service';
import { Router } from '@angular/router';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { HttpClient, HttpHeaders, HttpErrorResponse } from '@angular/common/http';
import { take, catchError } from 'rxjs/operators';
import { throwError } from 'rxjs';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit {
  form = new FormGroup({
    name: new FormControl('', [Validators.required]),
    email: new FormControl('', [Validators.required]),
    password: new FormControl('', [Validators.required]),
    confirmPassword: new FormControl('', [Validators.required])
  })

  constructor(private http: HttpClient, private signInService: SignInService, private router: Router) {
    this.form.get('password').valueChanges.subscribe(firstPass => {
      this.form.get('confirmPassword').setValidators([Validators.required, Validators.pattern(`^${firstPass}$`)])
    })
  }

  ngOnInit() {
  }

  register(): void {
    this.http.post('http://localhost:4201/NutritionalLookup', {}, { headers: new HttpHeaders({
      source: 'registration',
      fName: this.form.get('name').value.split(' ')[0],
      lName: this.form.get('name').value.split(' ')[1],
      email: this.form.get('email').value,
      user: this.form.get('email').value,
      password: this.form.get('password').value
    })}).pipe(take(1)).pipe(catchError(this.handleError)).subscribe(res => {
      this.signInService.setUser({
        email: this.form.get('email').value,
        password: this.form.get('password').value
      });
      this.signInService.setIsLoggedIn(true);
      this.router.navigateByUrl("/survey");
    })
  }

  handleError(error: HttpErrorResponse) {
     alert('Email already exists!');
     return throwError('');
   }
}
