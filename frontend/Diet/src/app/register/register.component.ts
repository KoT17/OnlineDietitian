import { Component, OnInit } from '@angular/core';
import { SignInService } from '../sign-in.service';
import { Router } from '@angular/router';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { take } from 'rxjs/operators';

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
  httpOptions = new HttpHeaders({
    "user": '',
    "password": '',
    "source": ''
  })

  constructor(private http: HttpClient, private signInService: SignInService, private router: Router) {
    this.form.get('password').valueChanges.subscribe(firstPass => {
      this.form.get('confirmPassword').setValidators([Validators.required, Validators.pattern(`^${firstPass}$`)])
    })
  }

  ngOnInit() {
  }

  register(): void {
    this.httpOptions.set('user', this.form.get('email').value);
    this.httpOptions.set('password', this.form.get('password').value);
    let body = {
      name: this.form.get('name').value,
      email: this.form.get('email').value
    }
    this.http.post('registerURL', body, { headers: this.httpOptions }).pipe(take(1)).subscribe(res => {
      if(res == "invalid") {
        alert('Email already exists!');
      } else {
        this.signInService.setUser(res);
        this.signInService.setIsLoggedIn(true);
        this.router.navigateByUrl("/survey");
      }
    })
  }
}
